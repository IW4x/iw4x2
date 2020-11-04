#include <std_include.hpp>
#include "console.hpp"
#include "loader/module_loader.hpp"
#include "game/game.hpp"
#include "scheduler.hpp"
#include <utils\string.hpp>

namespace dedicated_info
{
	class module final : public module_interface
	{
	public:
		void post_unpack() override
		{
			if (!game::environment::is_dedi())
			{
				return;
			}

			scheduler::once([]()
			{
				console::set_title("IW6x Dedicated Server");
				console::set_size(800, 600);
			});

			scheduler::loop([]()
			{
				auto sv_running = game::Dvar_FindVar("sv_running");

				if (!sv_running || !sv_running->current.enabled)
				{
					console::set_title("IW6x Dedicated Server");
					return;
				}

				const auto sv_hostname = game::Dvar_FindVar("sv_hostname");
				const auto sv_maxclients = game::Dvar_FindVar("sv_maxclients");
				const auto mapname = game::Dvar_FindVar("mapname");

				int client_count = 0;

				for (int i = 0; i < sv_maxclients->current.integer; i++)
				{
					auto client = &game::mp::svs_clients[i];
					auto self = &game::mp::g_entities[i];

					if (client->header.state >= 1 && self && self->client)
					{
						client_count++;
					}
				}

				std::string cleaned_hostname;
				cleaned_hostname.resize(static_cast<int>(strlen(sv_hostname->current.string) + 1));

				utils::string::strip(sv_hostname->current.string, cleaned_hostname.data(), static_cast<int>(strlen(sv_hostname->current.string)) + 1);

				console::set_title(utils::string::va("%s on %s [%d/%d]", cleaned_hostname.c_str(), mapname->current.string, client_count, sv_maxclients->current.integer));
			}, scheduler::pipeline::server, 1s);
		}
	};
}

REGISTER_MODULE(dedicated_info::module)
