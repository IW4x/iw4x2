#include <std_include.hpp>

#include "scheduler.hpp"
#include "loader/module_loader.hpp"
#include "utils/nt.hpp"
#include "utils/hook.hpp"
#include "game/game.hpp"

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
			"mp_character_room",
			"mp_character_room_heads",
			"mp_character_room_bodies_updated",
			"mp_character_room_dlc_updated",
			"techsets_common_core_mp",
			"common_core_mp",
			"common_core_dlc_updated_mp",
			"techsets_common_alien_mp",
			"common_alien_mp",
			"common_alien_dlc_updated_mp",
			0
		};

		// load fastfiles
		std::memcpy(reinterpret_cast<void*>(0x1480B1E40), &fastfiles, sizeof(fastfiles));

		// R_LoadGraphicsAssets
		reinterpret_cast<void(*)()>(0x1405E6F80)();
	}

	game::dvar_t* register_network_fps_stub(const char* name, int, int, int, unsigned int flags,
	                                    const char* desc)
	{
		return game::Dvar_RegisterInt(name, 1000, 50, 1000, flags, desc);
	}
}

class dedicated final : public module
{
public:
	void post_unpack() override
	{
		if (!game::environment::is_dedi())
		{
			return;
		}

		//utils::hook::set<uint8_t>(0x1402C89A0, 0xC3); // R_Init caller
		utils::hook::jump(0x1402C89A0, init_dedicated_server);
		utils::hook::call(0x140476F4F, register_network_fps_stub);

		utils::hook::set<uint8_t>(0x1402E5830, 0xC3); // disable self-registration
		utils::hook::set<uint8_t>(0x1402C7935, 5);    // make CL_Frame do client packets, even for game state 9
		//utils::hook::set<uint8_t>(0x5C6F90, 0xC3);  // init sound system (1)
		utils::hook::set<uint8_t>(0x140602380, 0xC3); // start render thread
		utils::hook::set<uint8_t>(0x140658580, 0xC3); // init sound system (2)
		//utils::hook::set<uint8_t>(0x49BC10, 0xC3);  // Com_Frame audio processor?
		utils::hook::set<uint8_t>(0x1402CF570, 0xC3); // called from Com_Frame, seems to do renderer stuff
		//utils::hook::set<uint8_t>(0x48FF30, 0xC3);  // CL_CheckForResend, which tries to connect to the local server constantly
		//utils::hook::set<uint8_t>(0x5CC160, 0xC3);  // function detecting video card, causes Direct3DCreate9 to be called
		utils::hook::set<uint8_t>(0x1405DAE1F, 0);    // r_loadForRenderer default to 0
		utils::hook::set<uint8_t>(0x1404FFCE2, 0xC3); // recommended settings check - TODO: Check hook
		utils::hook::set<uint8_t>(0x140503420, 0xC3); // some mixer-related function called on shutdown
		utils::hook::set<uint8_t>(0x1404BEC10, 0xC3); // dont load ui gametype stuff
		//utils::hook::set<uint8_t>(0x611690, 0xC3);  // some unknown function that seems to fail
		utils::hook::nop(0x14047261C, 6);             // unknown check in SV_ExecuteClientMessage
		//utils::hook::nop(0x5751DF, 2);              // don't spawn a DemonWare session for the dedicated server
		//utils::hook::set<uint8_t>(0x5751E9, 0xEB);  // ^
		utils::hook::nop(0x140471B6B, 4);             // allow first slot to be occupied
		utils::hook::nop(0x1402CA0F5, 2);             // properly shut down dedicated servers
		utils::hook::nop(0x1402CA0B9, 2);             // ^
		utils::hook::nop(0x1402CA12D, 5);             // don't shutdown renderer
		//utils::hook::set<uint8_t>(0x575266, 0xEB);  // shutdown existing stuff before loading new map
		
		utils::hook::set<uint8_t>(0x1404FFCF0, 0xC3); // cpu detection stuff
		utils::hook::set<uint8_t>(0x1405F0620, 0xC3); // gfx stuff during fastfile loading
		utils::hook::set<uint8_t>(0x1405F0530, 0xC3); // ^
		utils::hook::set<uint8_t>(0x1405F05C0, 0xC3); // ^
		utils::hook::set<uint8_t>(0x140324F00, 0xC3); // ^
		utils::hook::set<uint8_t>(0x1405F0580, 0xC3); // ^
		utils::hook::set<uint8_t>(0x1405B81A0, 0xC3); // directx stuff
		utils::hook::set<uint8_t>(0x1405E0CF0, 0xC3); // ^
		utils::hook::set<uint8_t>(0x1405E1530, 0xC3); // ^
		utils::hook::set<uint8_t>(0x1405E3E50, 0xC3); // ^
		utils::hook::set<uint8_t>(0x1405E1050, 0xC3); // ^

		utils::hook::set<uint8_t>(0x140167E00, 0xC3); // ^
		utils::hook::set<uint8_t>(0x140167D80, 0xC3); // ^

		utils::hook::set<uint8_t>(0x1406492A0, 0xC3); // ^

		utils::hook::set<uint8_t>(0x1405047A0, 0xC3); // idk
		utils::hook::set<uint8_t>(0x1405B8DB0, 0xC3); // ^

		utils::hook::set<uint8_t>(0x1405B8BD0, 0xC3); // shutdown stuff
		utils::hook::set<uint8_t>(0x1405E7DF0, 0xC3); // ^
		utils::hook::set<uint8_t>(0x1405E76C0, 0xC3); // ^

		utils::hook::set<uint8_t>(0x14065EA00, 0xC3); // sound crashes
		
		utils::hook::set<uint8_t>(0x14047BE70, 0xC3); // disable host migration
	}
};

#ifdef DEV_BUILD
REGISTER_MODULE(dedicated)
#endif
