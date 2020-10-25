#include <std_include.hpp>
#include "loader/module_loader.hpp"
#include "scheduler.hpp"
#include "server_list.hpp"
#include "network.hpp"
#include "command.hpp"
#include "utils/hook.hpp"
#include "game/game.hpp"
#include "utils/string.hpp"

namespace dedicated
{
	namespace
	{
		void init_dedicated_server()
		{
			static bool initialized = false;
			if (initialized) return;
			initialized = true;

			static const char* fastfiles[] =
			{
				"code_post_gfx_mp",
				"ui_mp",
				"code_nvidia_mp",
				"common_mp",
				nullptr, //"mp_character_room",
				nullptr, //"mp_character_room_heads",
				nullptr, //"mp_character_room_bodies_updated",
				nullptr, //"mp_character_room_dlc_updated",
				"techsets_common_core_mp",
				"common_core_mp",
				"common_core_dlc_updated_mp",
				"techsets_common_alien_mp",
				"common_alien_mp",
				"common_alien_dlc_updated_mp",
				nullptr
			};

			// load fastfiles
			std::memcpy(reinterpret_cast<void*>(0x1480B1E40), &fastfiles, sizeof(fastfiles));

			// R_LoadGraphicsAssets
			reinterpret_cast<void(*)()>(0x1405E6F80)();
		}

		game::dvar_t* register_maxfps_stub(const char* name, int, int, int, unsigned int flags,
		                                   const char* desc)
		{
			return game::Dvar_RegisterInt(name, 0, 0, 0, game::DvarFlags::DVAR_FLAG_READ, desc);
		}

		void send_heartbeat()
		{
			game::netadr_s target{};
			if (server_list::get_master_server(target))
			{
				network::send(target, "heartbeat", "IW6");
			}
		}

		std::vector<std::string>& get_command_queue()
		{
			static std::vector<std::string> command_queue;
			return command_queue;
		}

		void execute_console_command(const int client, const char* command)
		{
			if (game::Live_SyncOnlineDataFlags(0) == 0)
			{
				game::Cbuf_AddText(client, command);
				game::Cbuf_AddText(client, "\n");
			}
			else
			{
				get_command_queue().emplace_back(command);
			}
		}

		void execute_command_queue()
		{
			const auto queue = get_command_queue();
			get_command_queue().clear();

			for (const auto& command : queue)
			{
				game::Cbuf_AddText(0, command.data());
				game::Cbuf_AddText(0, "\n");
			}
		}

		volatile bool allow_lobby_pump = true;
		utils::hook::detour lobby_pump_hook;

		void lobby_pump_stub(const int controller_index)
		{
			if (allow_lobby_pump)
			{
				allow_lobby_pump = false;
				lobby_pump_hook.invoke<void*>(controller_index);
			}
		}

		volatile bool allow_net_pump = true;
		utils::hook::detour net_pump_hook;

		void net_pump_stub(const int controller_index)
		{
			if (allow_net_pump)
			{
				allow_net_pump = false;
				net_pump_hook.invoke<void*>(controller_index);
			}
		}

		game::DWOnlineStatus get_logon_status_stub(const int controller_index)
		{
			static auto is_connected = false;
			if (is_connected)
			{
				return game::DW_LIVE_CONNECTED;
			}

			const auto result = reinterpret_cast<game::DWOnlineStatus(*)(int)>(0x1405894C0)(controller_index);
			if (result == game::DW_LIVE_CONNECTED)
			{
				is_connected = true;
				lobby_pump_hook.create(0x140591850, lobby_pump_stub);
				net_pump_hook.create(0x140558C20, net_pump_stub);
			}

			return result;
		}
	}

	class module final : public module_interface
	{
	public:
		void post_unpack() override
		{
			if (!game::environment::is_dedi())
			{
				return;
			}

			/*scheduler::loop([]
			{
				allow_lobby_pump = true;
				allow_net_pump = true;
			}, scheduler::pipeline::async, 300ms);*/

			// Some arxan exception stuff to obfuscate functions
			// This is causing lags
			// We will have to properly patch that some day
			//utils::hook::jump(0x140589480, get_logon_status_stub);

			//utils::hook::set<uint8_t>(0x1402C89A0, 0xC3); // R_Init caller
			utils::hook::jump(0x1402C89A0, init_dedicated_server);
			utils::hook::call(0x140413AD8, register_maxfps_stub);

			// delay console commands until the initialization is done
			utils::hook::call(0x140412FD3, execute_console_command);
			utils::hook::nop(0x140412FE9, 5);

			utils::hook::nop(0x1404DDC2E, 5); // don't load config file
			utils::hook::set<uint8_t>(0x140416100, 0xC3); // don't save config file
			utils::hook::set<uint8_t>(0x1402E5830, 0xC3); // disable self-registration
			utils::hook::set<uint8_t>(0x1402C7935, 5); // make CL_Frame do client packets, even for game state 9
			utils::hook::set<uint8_t>(0x140503FF0, 0xC3); // init sound system (1)
			utils::hook::set<uint8_t>(0x140602380, 0xC3); // start render thread
			utils::hook::set<uint8_t>(0x140658580, 0xC3); // init sound system (2)
			//utils::hook::set<uint8_t>(0x49BC10, 0xC3);  // Com_Frame audio processor?
			utils::hook::set<uint8_t>(0x1402CF570, 0xC3); // called from Com_Frame, seems to do renderer stuff
			utils::hook::set<uint8_t>(0x1402C49B0, 0xC3);
			// CL_CheckForResend, which tries to connect to the local server constantly
			utils::hook::set<uint8_t>(0x1405DAE1F, 0); // r_loadForRenderer default to 0
			utils::hook::set<uint8_t>(0x1404FFCE2, 0xC3); // recommended settings check - TODO: Check hook
			utils::hook::set<uint8_t>(0x140503420, 0xC3); // some mixer-related function called on shutdown
			utils::hook::set<uint8_t>(0x1404BEC10, 0xC3); // dont load ui gametype stuff
			//utils::hook::set<uint8_t>(0x611690, 0xC3);  // some unknown function that seems to fail
			utils::hook::nop(0x14047261C, 6); // unknown check in SV_ExecuteClientMessage
			//utils::hook::nop(0x5751DF, 2);              // don't spawn a DemonWare session for the dedicated server
			//utils::hook::set<uint8_t>(0x5751E9, 0xEB);  // ^
			utils::hook::nop(0x140471B6B, 4); // allow first slot to be occupied
			utils::hook::nop(0x1402CA0F5, 2); // properly shut down dedicated servers
			utils::hook::nop(0x1402CA0B9, 2); // ^
			utils::hook::nop(0x1402CA12D, 5); // don't shutdown renderer
			utils::hook::set<uint8_t>(0x1405E87DE, 0xEB); // ignore world being in use

			utils::hook::set<uint8_t>(0x1404FFCF0, 0xC3); // cpu detection stuff
			utils::hook::set<uint8_t>(0x1405F0620, 0xC3); // gfx stuff during fastfile loading
			utils::hook::set<uint8_t>(0x1405F0530, 0xC3); // ^
			utils::hook::set<uint8_t>(0x1405F05C0, 0xC3); // ^
			utils::hook::set<uint8_t>(0x140324F00, 0xC3); // ^
			utils::hook::set<uint8_t>(0x1405F0580, 0xC3); // ^
			utils::hook::set<uint8_t>(0x1405B81A0, 0xC3); // directx stuff
			utils::hook::set<uint8_t>(0x1405E0CF0, 0xC3); // ^
			utils::hook::set<uint8_t>(0x1405E1530, 0xC3); // ^
			utils::hook::set<uint8_t>(0x1405E3E50, 0xC3); // ^ - mutex
			utils::hook::set<uint8_t>(0x1405E1050, 0xC3); // ^

			// shaders
			utils::hook::set<uint8_t>(0x140167E00, 0xC3); // ^
			utils::hook::set<uint8_t>(0x140167D80, 0xC3); // ^

			utils::hook::set<uint8_t>(0x1406492A0, 0xC3); // ^ - mutex

			utils::hook::set<uint8_t>(0x1405047A0, 0xC3); // idk
			utils::hook::set<uint8_t>(0x1405B8DB0, 0xC3); // ^

			utils::hook::set<uint8_t>(0x1405E7D20, 0xC3); // R_Shutdown
			utils::hook::set<uint8_t>(0x1405B8BD0, 0xC3); // shutdown stuff
			utils::hook::set<uint8_t>(0x1405E7DF0, 0xC3); // ^
			utils::hook::set<uint8_t>(0x1405E76C0, 0xC3); // ^

			utils::hook::set<uint8_t>(0x14065EA00, 0xC3); // sound crashes

			utils::hook::set<uint8_t>(0x14047BE70, 0xC3); // disable host migration

			utils::hook::set<uint8_t>(0x140423B20, 0xC3); // render synchronization lock
			utils::hook::set<uint8_t>(0x140423A60, 0xC3); // render synchronization unlock

			//utils::hook::set<uint8_t>(0x1405E3470, 0xC3); // some rendering stuff in R_UpdateDynamicMemory
			//utils::hook::set<uint8_t>(0x1405E31A0, 0xC3); // ^
			utils::hook::jump(0x140610EB6, 0x140610F15); // ^

			utils::hook::nop(0x1404F8BD9, 5); // Disable sound pak file loading
			utils::hook::nop(0x1404F8BE1, 2); // ^
			utils::hook::set<uint8_t>(0x140328660, 0xC3); // Disable image pak file loading

			scheduler::on_game_initialized([]()
			{
				game::Cmd_ExecuteSingleCommand(0, 0, "xstartprivatematch\n");
				game::Cmd_ExecuteSingleCommand(0, 0, "xstartpartyhost\n");

				game::Cmd_ExecuteSingleCommand(0, 0, "exec default_mp_gamesettings.cfg\n");
				game::Cmd_ExecuteSingleCommand(0, 0, "exec default_private.cfg\n");
				game::Cmd_ExecuteSingleCommand(0, 0, "onlinegame 1\n");
				game::Cmd_ExecuteSingleCommand(0, 0, "xblive_rankedmatch 1\n");
				game::Cmd_ExecuteSingleCommand(0, 0, "xblive_privatematch 1\n");

				printf("==================================\n");
				printf("Server started!\n");
				printf("==================================\n");

				execute_command_queue();
			}, scheduler::pipeline::main, 1s);

			// Send heartbeat to dpmaster
			scheduler::once(send_heartbeat, scheduler::pipeline::server);
			scheduler::loop(send_heartbeat, scheduler::pipeline::server, 2min);
			command::add("heartbeat", send_heartbeat);

			command::add("clientkick", [](command::params& params)
			{
				if (params.size() < 3)
				{
					return;
				}

				auto client = atoi(params.get(1));
				std::string reason = params.join(2);

				game::SV_GameSendServerCommand(client, 0, utils::string::va("r \"%s\"", reason.data()));
			});
		}
	};
}

REGISTER_MODULE(dedicated::module)
