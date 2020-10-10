#include <std_include.hpp>
#include "logs.hpp"

#include "game/game.hpp"

#include "utils/io.hpp"
#include "utils/string.hpp"

#define LOGS_FOLDER "logs"

std::string logs::game_console::buffer;

void logs::game_console::log(const char* message, ...)
{
	auto s = utils::string::va("[%s] %s\n", logs::get_log_time().data(), message);
	logs::game_console::buffer.append(s);
}

bool logs::game_console::save()
{
	return utils::io::write_file(utils::string::va("%s/%s", LOGS_FOLDER, "game_console.log"), logs::game_console::buffer, false);
}

void logs::pre_destroy()
{
	logs::game_console::save();
}

std::string logs::get_log_time()
{
	auto s = std::to_string(game::Sys_Milliseconds());
	while (s.size() < 10)
	{
		s.insert(0, " ");
	}
	return s;
}

REGISTER_MODULE(logs);
