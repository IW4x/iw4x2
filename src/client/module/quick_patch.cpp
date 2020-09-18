#include <std_include.hpp>
#include "quick_patch.hpp"
#include "game/game.hpp"
#include "module/command.hpp"
#include "module/game_console.hpp"

quick_patch::quick_patch()
{

}

void quick_patch::post_unpack()
{
	// patch com_maxfps
	game::native::Dvar_RegisterInt("com_maxfps", 85, 0, 1000, 0x1, "Cap frames per second"); // changed max value from 85 -> 1000

	// patch cg_fov
	game::native::Dvar_RegisterFloat("cg_fov", 65.0f, 65.0f, 120.0f, 0x1, "The field of view angle in degrees"); // changed max value from 80.0f -> 120.f

	// patch r_vsync
	game::native::Dvar_RegisterBool("r_vsync", false, 0x1, "Enable v-sync before drawing the next frame to avoid 'tearing' artifacts."); // changed default value from true -> false. There are some fps issues with vsync at least on 144hz monitors.

	// add quit command
	command::add("quit", [](command::params&)
	{
		// Should be Game::Com_Quit_f();
		exit(0);
	});

	// add getDvarValue command
	command::add("getDvarValue", [](command::params& params)
	{
		auto param = params.get(1);
		auto dvar = game::native::Dvar_FindVar(param);
		if (dvar)
			return game_console::print(7, "%s\n", game::native::Dvar_ValueToString(dvar, dvar->current));
		return game_console::print(1, "Dvar %s not found\n", param);
	});

	// add dvarDump command
	command::add("dvarDump", [](command::params&)
	{
		game_console::print(7, "================================ DVAR DUMP ========================================\n");
		int i;
		for (i = 0; i < *game::native::dvarCount; i++)
		{
			if (game::native::sortedDvars[i] && game::native::sortedDvars[i]->name)
			{
				game_console::print(7, "%s\n", game::native::sortedDvars[i]->name);
			}
		}
		game_console::print(7, "\n%i dvar indexes\n", i);
		game_console::print(7, "================================ END DVAR DUMP ====================================\n");
	});

	// add commandDump command
	command::add("commandDump", [](command::params&)
	{
		game_console::print(7, "================================ COMMAND DUMP =====================================\n");
		game::native::cmd_function_s* cmd = (*game::native::cmd_functions);
		int i = 0;
		while (cmd)
		{
			if (cmd->name)
			{
				game_console::print(7, "%s\n", cmd->name);
				i++;
			}
			cmd = cmd->next;
		}
		game_console::print(7, "\n%i command indexes\n", i);
		game_console::print(7, "================================ END COMMAND DUMP =================================\n");
	});
}

REGISTER_MODULE(quick_patch);