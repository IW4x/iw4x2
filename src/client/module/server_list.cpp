#include <std_include.hpp>
#include "server_list.hpp"

#include "game/game.hpp"
#include "game/dvars.hpp"

#include "command.hpp"
#include "game_console.hpp"
#include "localized_strings.hpp"
#include "scheduler.hpp"

#include "utils/string.hpp"

bool server_list::update_server_list;
int server_list::server_count;

int server_list::display_servers[MAX_SERVERS];
server_info server_list::servers[MAX_SERVERS];

void server_list::insert_server(server_info* server)
{
	int position = server_count;

	if (server_count >= MAX_SERVERS)
	{
		position = 0;

		for (int i = 0; i < MAX_SERVERS; i++)
		{
			if (servers[i].ping > servers[position].ping)
			{
				position = i;
			}
		}
	}
	else
	{
		InterlockedIncrement(reinterpret_cast<long volatile*>(&server_count));
	}

	memcpy(&servers[position], server, sizeof(server_info));
}

void server_list::add_server()
{
	server_info server = { 0 };

	strcpy_s(server.host_name, utils::string::va("^%dIW6x Test Server %d", server_count + 1, server_count));
	strcpy_s(server.map_name, "mp_favela_iw6");
	strcpy_s(server.game_type, "war");

	server.clients = 0;
	server.max_clients = 18;
	server.ping = rand() % 999;

	server.in_game = 0;

	insert_server(&server);

	update_server_list = true;
}

void lui_open_menu_stub(int controllerIndex, const char* menu, int a3, int a4, unsigned int a5)
{
	game::Cmd_ExecuteSingleCommand(0, 0, "lui_open menu_systemlink_join\n");
}

void refresh_server_list()
{
	// refresh server list here
}

void join_server(int, int, const int index)
{
	printf("Join %d ...\n", index);
}

bool server_list_refresher()
{
	if (server_list::update_server_list)
	{
		server_list::update_server_list = false;
	}

	return 0;
}

int server_list::ui_feeder_count()
{
	return server_list::server_count;
}

const char* server_list::ui_feeder_item_text(int localClientNum, void* a2, void* a3, int index, int column)
{
	if (column == 0)
	{
		return servers[index].host_name;
	}
	else if (column == 1)
	{
		return servers[index].map_name;
	}
	else if (column == 2)
	{
		return utils::string::va("%d/%d", servers[index].clients, servers[index].max_clients);
	}
	else if (column == 3)
	{
		return servers[index].game_type;
	}

	return "";
}

void server_list::post_unpack()
{
	if (!game::environment::is_mp()) return;

	localized_strings::override("PLATFORM_SYSTEM_LINK_TITLE", "SERVER LIST");
	localized_strings::override("LUA_MENU_STORE_CAPS", "SERVER LIST");
	localized_strings::override("LUA_MENU_STORE_DESC", "Browse available servers.");

	// hook LUI_OpenMenu to show server list instead of store popup
	utils::hook::call(0x1404FE840, &lui_open_menu_stub);

	// refresh server list when needed
	utils::hook::call(0x1402F7480, &server_list_refresher);

	// replace UI_RunMenuScript call in LUI_CoD_LuaCall_RefreshServerList to our refresh_servers
	utils::hook::call(0x1401E7171, &refresh_server_list);
	utils::hook::call(0x1401E7616, &join_server);
	utils::hook::nop(0x1401E7635, 5);

	// do feeder stuff
	utils::hook::call(0x1401E7225, &ui_feeder_count);
	utils::hook::call(0x1401E7405, &ui_feeder_item_text);

	memset(display_servers, 0, sizeof(display_servers));
	memset(servers, 0, sizeof(servers));

	command::add("addTestServer", [&](command::params&)
	{
		add_server();
	});

	command::add("clearTestServers", [&](command::params&)
	{
		memset(display_servers, 0, sizeof(display_servers));
		memset(servers, 0, sizeof(servers));

		server_count = 0;
	});
	
	command::add("lui_open", [](command::params params)
	{
		if (params.size() <= 1)
		{
			game_console::print(7, "usage: lui_open <name>\n");
			return;
		}

		game::LUI_OpenMenu(0, params[1], 1, 0, 0);
	});
}

REGISTER_MODULE(server_list);