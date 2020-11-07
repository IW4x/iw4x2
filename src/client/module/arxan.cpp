#include <std_include.hpp>
#include "loader/module_loader.hpp"
#include "scheduler.hpp"
#include "game/game.hpp"
#include "utils/hook.hpp"

namespace arxan
{
	namespace
	{
		typedef struct _OBJECT_HANDLE_ATTRIBUTE_INFORMATION
		{
			BOOLEAN Inherit;
			BOOLEAN ProtectFromClose;
		} OBJECT_HANDLE_ATTRIBUTE_INFORMATION;

		utils::hook::detour nt_close_hook;
		utils::hook::detour nt_query_information_process_hook;

		NTSTATUS WINAPI nt_query_information_process_stub(const HANDLE handle, const PROCESSINFOCLASS info_class,
		                                                  PVOID info,
		                                                  const ULONG info_length, const PULONG ret_length)
		{
			auto* orig = static_cast<decltype(NtQueryInformationProcess)*>(nt_query_information_process_hook.
				get_original());
			const auto status = orig(handle, info_class, info, info_length, ret_length);

			if (NT_SUCCESS(status))
			{
				if (info_class == ProcessBasicInformation)
				{
					static DWORD explorerPid = 0;
					if (!explorerPid)
					{
						auto* const shell_window = GetShellWindow();
						GetWindowThreadProcessId(shell_window, &explorerPid);
					}

					static_cast<PPROCESS_BASIC_INFORMATION>(info)->Reserved3 = PVOID(DWORD64(explorerPid));
				}
				else if (info_class == 30) // ProcessDebugObjectHandle
				{
					*static_cast<HANDLE*>(info) = nullptr;

					return 0xC0000353;
				}
				else if (info_class == 7) // ProcessDebugPort
				{
					*static_cast<HANDLE*>(info) = nullptr;
				}
				else if (info_class == 31)
				{
					*static_cast<ULONG*>(info) = 1;
				}
			}

			return status;
		}

		NTSTATUS NTAPI nt_close_stub(const HANDLE handle)
		{
			char info[16];
			if (NtQueryObject(handle, OBJECT_INFORMATION_CLASS(4), &info, sizeof(OBJECT_HANDLE_ATTRIBUTE_INFORMATION),
			                  nullptr) >= 0)
			{
				auto* orig = static_cast<decltype(NtClose)*>(nt_close_hook.get_original());
				return orig(handle);
			}

			return STATUS_INVALID_HANDLE;
		}

		LONG WINAPI exception_filter(LPEXCEPTION_POINTERS info)
		{
			return (info->ExceptionRecord->ExceptionCode == STATUS_INVALID_HANDLE)
				       ? EXCEPTION_CONTINUE_EXECUTION
				       : EXCEPTION_CONTINUE_SEARCH;
		}

		void hide_being_debugged()
		{
			auto* const peb = PPEB(__readgsqword(0x60));
			peb->BeingDebugged = false;
			*PDWORD(LPSTR(peb) + 0xBC) &= ~0x70;
		}

		BOOL WINAPI set_thread_context_stub(const HANDLE thread, CONTEXT* context)
		{
			// TODO: Disable HW breakpoints, once the dw frame is patched
			return SetThreadContext(thread, context);
		}

		void dw_frame_stub(size_t index)
		{
			const auto dwGetLogOnStatus = reinterpret_cast<game::DWOnlineStatus(*)(size_t)>(0x140589490);
			const auto status = dwGetLogOnStatus(index);

			if (status == game::DW_LIVE_CONNECTING)
			{
				// dwLogOnComplete
				reinterpret_cast<void(*)(size_t)>(0x1405894D0)(index);
			}
			else if (status == game::DW_LIVE_DISCONNECTED)
			{
				// dwLogOnStart
				reinterpret_cast<void(*)(size_t)>(0x140589E10)(index);
			}
			else
			{
				// dwLobbyPump
				//reinterpret_cast<void(*)(size_t)>(0x1405918E0)(index);

				// DW_Frame
				reinterpret_cast<void(*)(size_t)>(0x14000F9A6)(index);
			}
		}
	}

	class module final : public module_interface
	{
	public:
		void* load_import(const std::string& module, const std::string& function) override
		{
			if (function == "SetThreadContext")
			{
				return set_thread_context_stub;
			}
			return nullptr;
		}

		void post_load() override
		{
			hide_being_debugged();
			scheduler::loop(hide_being_debugged, scheduler::pipeline::async);

			const utils::nt::module ntdll("ntdll.dll");
			nt_close_hook.create(ntdll.get_proc<void*>("NtClose"), nt_close_stub);
			nt_query_information_process_hook.create(ntdll.get_proc<void*>("NtQueryInformationProcess"),
			                                         nt_query_information_process_stub);

			AddVectoredExceptionHandler(1, exception_filter);
		}

		void post_unpack() override
		{
			// cba to implement sp, not sure if it's even needed
			if (game::environment::is_sp()) return;

			utils::hook::jump(0x1404FE1E0, 0x1404FE2D0); // idk
			utils::hook::jump(0x140558C20, 0x140558CB0); // dwNetPump
			utils::hook::jump(0x140591850, 0x1405918E0); // dwLobbyPump
			utils::hook::jump(0x140589480, 0x140589490); // dwGetLogonStatus

			// These two are inlined with their synchronization. Need to work around that
			//utils::hook::jump(0x14015EB9A, 0x140589E10); // dwLogOnStart
			//utils::hook::call(0x140588306, 0x1405894D0); // dwLogOnComplete

			// Unfinished for now
			//utils::hook::jump(0x1405881E0, dw_frame_stub);
		}
	};
}

REGISTER_MODULE(arxan::module)
