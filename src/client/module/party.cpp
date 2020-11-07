#include <std_include.hpp>
#include "loader/module_loader.hpp"
#include "party.hpp"

#include "command.hpp"
#include "network.hpp"
#include "scheduler.hpp"
#include "server_list.hpp"

#include "steam/steam.hpp"

#include "utils/string.hpp"
#include "utils/info_string.hpp"
#include "utils/cryptography.hpp"

namespace party
{
	namespace
	{
		struct
		{
			game::netadr_s host{};
			std::string challenge{};
		} connect_state;

		void switch_gamemode_if_necessary(const std::string& gametype)
		{
			const auto target_mode = gametype == "aliens" ? game::CODPLAYMODE_ALIENS : game::CODPLAYMODE_CORE;
			const auto current_mode = game::Com_GetCurrentCoDPlayMode();

			if (current_mode != target_mode)
			{
				switch (target_mode)
				{
				case game::CODPLAYMODE_CORE:
					game::SwitchToCoreMode();
					break;
				case game::CODPLAYMODE_ALIENS:
					game::SwitchToAliensMode();
					break;
				}
			}
		}

		void connect_to_party(const game::netadr_s& target, const std::string& mapname, const std::string& gametype)
		{
			if (game::environment::is_sp())
			{
				return;
			}

			if (game::Live_SyncOnlineDataFlags(0))
			{
				scheduler::once([=]()
				{
					connect_to_party(target, mapname, gametype);
				}, scheduler::pipeline::main, 1s);
				return;
			}

			switch_gamemode_if_necessary(gametype);

			// This fixes several crashes and impure client stuff
			command::execute("onlinegame 1", true);
			command::execute("exec default_xboxlive.cfg", true);
			command::execute("xstartprivateparty", true);
			command::execute("xblive_rankedmatch 1", true);
			command::execute("xblive_privatematch 1", true);
			command::execute("startentitlements", true);

			// CL_ConnectFromParty
			char session_info[0x100] = {};
			reinterpret_cast<void(*)(int, char*, const game::netadr_s*, const char*, const char*)>(0x1402C5700)(
				0, session_info, &target, mapname.data(), gametype.data());
		}

		std::string get_dvar_string(const std::string& dvar)
		{
			auto* dvar_value = game::Dvar_FindVar(dvar.data());
			if (dvar_value && dvar_value->current.string)
			{
				return dvar_value->current.string;
			}

			return {};
		}

		int get_client_count()
		{
			auto count = 0;
			for (auto i = 0; i < *game::mp::svs_numclients; ++i)
			{
				if (game::mp::svs_clients[i].header.state >= 3)
				{
					++count;
				}
			}

			return count;
		}
	}

	int get_client_num_from_name(std::string name)
	{
		for (auto i = 0; !name.empty() && i < *game::mp::svs_numclients; ++i)
		{
			char client_name[16] = { 0 };
			strncpy_s(client_name, game::mp::g_entities[i].client->sess.cs.name, 16);
			game::I_CleanStr(client_name);

			if (client_name == name)
			{
				return i;
			}
		}
		return -1;
	}

	void connect(const game::netadr_s& target)
	{
		if (game::environment::is_sp())
		{
			return;
		}

		command::execute("lui_open popup_acceptinginvite", false);

		connect_state.host = target;
		connect_state.challenge = utils::cryptography::random::get_challenge();

		network::send(target, "getInfo", connect_state.challenge);
	}

	void start_map(const std::string& mapname)
	{
		if (game::Live_SyncOnlineDataFlags(0) != 0)
		{
			scheduler::on_game_initialized([mapname]()
			{
				//start_map(mapname);
				command::execute("map " + mapname, false);
			}, scheduler::pipeline::main, 1s);
		}
		else
		{
			printf("Starting map: %s\n", mapname.data());
			switch_gamemode_if_necessary(get_dvar_string("g_gametype"));
			game::SV_StartMapForParty(0, mapname.data(), false, false);
		}
	}

	class module final : public module_interface
	{
	public:
		void post_unpack() override
		{
			if (game::environment::is_sp())
			{
				return;
			}

			command::add("map", [](command::params& argument)
			{
				if (argument.size() != 2)
				{
					return;
				}

				start_map(argument[1]);
			});

			command::add("fast_restart", []()
			{
				if (game::SV_Loaded())
				{
					game::SV_FastRestart();
				}
			});

			command::add("connect", [](command::params& argument)
			{
				if (argument.size() != 2)
				{
					return;
				}

				game::netadr_s target{};
				if (game::NET_StringToAdr(argument[1], &target))
				{
					connect(target);
				}
			});

			command::add("clientkick", [](command::params& params)
			{
				if (params.size() < 2)
				{
					printf("usage: clientkick <num>\n");
					return;
				}
				auto clientNum = atoi(params.get(1));
				if (clientNum < 0 || clientNum >= *game::mp::svs_numclients)
				{
					return;
				}

				game::SV_KickClientNum(clientNum, "EXE_PLAYERKICKED");
			});

			command::add("kick", [](command::params& params)
			{
				if (params.size() < 2)
				{
					printf("usage: kick <name>\n");
					return;
				}
				auto name = params.get(1);

				if (name == "all"s)
				{
					for (auto i = 0; i < *game::mp::svs_numclients; ++i)
					{
						game::SV_KickClientNum(i, "EXE_PLAYERKICKED");
					}
					return;
				}

				auto clientNum = get_client_num_from_name(name);
				if (clientNum < 0 || clientNum >= *game::mp::svs_numclients)
				{
					return;
				}

				game::SV_KickClientNum(clientNum, "EXE_PLAYERKICKED");
			});

			network::on("getInfo", [](const game::netadr_s& target, const std::string_view& data)
			{
				utils::info_string info{};
				info.set("challenge", std::string{data});
				info.set("gamename", "IW6");
				info.set("hostname", get_dvar_string("sv_hostname"));
				info.set("gametype", get_dvar_string("g_gametype"));
				info.set("xuid", utils::string::va("%llX", steam::SteamUser()->GetSteamID().bits));
				info.set("mapname", get_dvar_string("mapname"));
				info.set("isPrivate", get_dvar_string("g_password").empty() ? "0" : "1");
				info.set("clients", utils::string::va("%i", get_client_count()));
				info.set("sv_maxclients", utils::string::va("%i", *game::mp::svs_numclients));
				info.set("protocol", utils::string::va("%i", PROTOCOL));
				//info.set("shortversion", SHORTVERSION);
				//info.set("hc", (Dvar::Var("g_hardcore").get<bool>() ? "1" : "0"));

				network::send(target, "infoResponse", info.build(), '\n');
			});

			network::on("infoResponse", [](const game::netadr_s& target, const std::string_view& data)
			{
				const utils::info_string info{data};
				server_list::handle_info_response(target, info);

				if (connect_state.host != target)
				{
					return;
				}

				if (info.get("challenge") != connect_state.challenge)
				{
					printf("Invalid challenge.\n");
					return;
				}

				const auto mapname = info.get("mapname");
				if (mapname.empty())
				{
					printf("Invalid map.\n");
					return;
				}

				const auto gametype = info.get("gametype");
				if (gametype.empty())
				{
					printf("Invalid gametype.\n");
					return;
				}

				connect_to_party(target, mapname, gametype);
			});
		}
	};
}

REGISTER_MODULE(party::module)
