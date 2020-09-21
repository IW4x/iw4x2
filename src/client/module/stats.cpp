#include <std_include.hpp>

#include "module/command.hpp"
#include "module/game_console.hpp"
#include "game/game.hpp"
#include "game/dvars.hpp"

#include "utils/hook.hpp"
#include "utils/nt.hpp"



class patches final : public module
{
public:
	void post_unpack() override
	{
		// igs_announcer
		// set it to 3 to display both voice dlc announcers did only show 1
		game::native::Dvar_RegisterInt("igs_announcer", 3, 3, 3, 0x0, "Show Announcer Packs. (Bitfield representing which announcer paks to show)");

		// apply mode specific patches
		if (game::is_mp())
		{
			patch_mp();
		}
	}

	void patch_mp() const
	{

		// add Unlock all Command - only does level for squad member 1 if people want level 60 on all squad members let me know and I can just add the rest of the squad members
		command::add("unlockall", [](command::params&)
			{

				//only Mp
				utils::hook::set<BYTE>(0x1445A3798, 0x0A);	// Prestige
				utils::hook::set<int64_t>(0x1445A34A0, 5000000); // squad points
				// squad member ranks
				for (int i = 0; i < 10; i++)
				{
					utils::hook::set<short>(0x14459F857 + (0x564, i), 0x12C5);
				}
				//squad members unlocked
				for (int i = 0; i < 9; i++)
				{
					utils::hook::set<short>(0x14459FD97 + (0x564, i), 0x0100);
				}
				//only Extinction
				utils::hook::set<short>(0x1445A6B62, 9999);	// Teeth
				utils::hook::set<BYTE>(0x1445A5F96, 25);	// Prestige
				utils::hook::set<short>(0x1445A5F90, 27);	// level

			});

	}
};