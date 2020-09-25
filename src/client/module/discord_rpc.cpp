#include <std_include.hpp>

#include "scheduler.hpp"

#include "game/game.hpp"
#include "game/dvars.hpp"

#include "discord_register.h"
#include "discord_rpc.h"
#include "localized_strings.hpp"

#include "utils/string.hpp"
#include <string.h>

namespace
{
	DiscordEventHandlers handlers;
	DiscordRichPresence discordPresence;
	auto ingame = false;

	int get_player_count()
	{
		auto maxclients = game::native::Dvar_FindVar("sv_maxclients")->current.integer;
		auto count = 0;
		for (auto i = 0; i < maxclients; i++) {
			if (game::native::mp::g_entities[i].s.entityType) {
				count++;
			}
		}
		return count;
	}

	void tick()
	{
		discordPresence.largeImageKey = "iw6x";

		if (!game::is_mp())
		{
			discordPresence.details = game::native::SEH_StringEd_GetString("DISCORDRPC_SP_TITLE");
			Discord_UpdatePresence(&discordPresence);
			return;
		}

		discordPresence.partySize = 0;
		discordPresence.partyMax = 0;

		discordPresence.details = game::native::Dvar_FindVar("g_gametype") ? strstr(game::native::Dvar_FindVar("g_gametype")->current.string, "aliens") ? game::native::SEH_StringEd_GetString("DISCORDRPC_ZM_TITLE") : game::native::SEH_StringEd_GetString("DISCORDRPC_MP_TITLE") : "";
		discordPresence.state = game::native::SEH_StringEd_GetString("DISCORDRPC_MAIN_MENU");

		if (game::native::SV_Loaded())
		{
			discordPresence.partySize = get_player_count();
			discordPresence.partyMax = game::native::Dvar_FindVar("sv_maxclients")->current.integer;

			discordPresence.state = strstr(game::native::Dvar_FindVar("net_ip")->current.string, "localhost") ? game::native::SEH_StringEd_GetString("DISCORDRPC_PRIVATE_MATCH") : game::native::Dvar_FindVar("sv_hostname")->current.string;
			discordPresence.details = utils::string::va(game::native::SEH_StringEd_GetString("DISCORDRPC_MATCH_TEMPLATE"), game::native::Dvar_FindVar("party_gametype")->current.string, game::native::Dvar_FindVar("party_mapname")->current.string);
		}

		if (!ingame)
			discordPresence.startTimestamp = game::native::SV_Loaded() ? std::time(0) : NULL;

		ingame = game::native::SV_Loaded();

		Discord_UpdatePresence(&discordPresence);
	}
}

class discord_rpc final : public module
{
public:
	void post_unpack() override
	{
		localized_strings::override("DISCORDRPC_MP_TITLE", "Multiplayer");
		localized_strings::override("DISCORDRPC_SP_TITLE", "Singleplayer");
		localized_strings::override("DISCORDRPC_ZM_TITLE", "Extinction");
		localized_strings::override("DISCORDRPC_MATCH_TEMPLATE", "%s on %s");
		localized_strings::override("DISCORDRPC_PRIVATE_MATCH", "Private Match");
		localized_strings::override("DISCORDRPC_MAIN_MENU", "Main menu");

		memset(&handlers, 0, sizeof(handlers));
		Discord_Initialize("757965986954477690", &handlers, 1, "");
		discordPresence.startTimestamp = std::time(0);
		scheduler::loop(tick, scheduler::pipeline::async);
	}
};

REGISTER_MODULE(discord_rpc);