#include <std_include.hpp>
#include "module/command.hpp"
#include "module/game_console.hpp"
#include "game/game.hpp"
#include "game/dvars.hpp"
#include "utils/hook.hpp"
#include "utils/nt.hpp"

class stats final : public module
{
public:
	void post_unpack() override
	{
		if (game::is_mp())
		{
			patch_mp();
		}
	}

	void patch_mp() const
	{
		// add Unlock all Command
		command::add("unlockall", [](command::params&)
		{
			utils::hook::set<BYTE>(0x1445A3798, 0x0A);	// Prestige
			utils::hook::set<short>(0x1445A34A0, 5000); // squad points
			//squad member ranks
			for (long long i = 0; i < 10; i++)
			{
				utils::hook::set<int>(0x14459F857 + (0x564 * i), 4805);
			}
			//squad members unlocked
			for (int i = 0; i < 9; i++)
			{
				utils::hook::set<short>(0x14459FD97 + (0x564 * i), 0x0100);
			}
			//only Extinction
			utils::hook::set<short>(0x1445A6B62, 9999);	// Teeth
			utils::hook::set<BYTE>(0x1445A5F96, 25);	// Prestige
			utils::hook::set<short>(0x1445A5F90, 27);	// level

		});
	}
};

REGISTER_MODULE(stats);
