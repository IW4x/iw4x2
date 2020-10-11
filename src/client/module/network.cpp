#include <std_include.hpp>
#include "network.hpp"

#include "game/game.hpp"
#include "utils/hook.hpp"

namespace
{
	std::unordered_map<std::string, network::callback>& get_callbacks()
	{
		static std::unordered_map<std::string, network::callback> callbacks{};
		return callbacks;
	}

	bool handle_command(game::netadr_s* address, const char* command, game::msg_t* message)
	{
		auto& callbacks = get_callbacks();
		const auto handler = callbacks.find(command);
		if (handler == callbacks.end())
		{
			return false;
		}

		const auto offset = strlen(command) + 5;
		const std::string_view data(message->data + offset, message->cursize - offset);

		handler->second(*address, data);
		return true;
	}

	void handle_command_stub(utils::hook::assembler& a)
	{
		const auto return_unhandled = a.newLabel();

		a.pushad64();

		a.mov(r8, rsi); // message
		a.mov(rdx, rdi); // command
		a.mov(rcx, r14); // netaddr

		a.call(handle_command);

		a.test(al, al);
		a.jz(return_unhandled);

		// Command handled
		a.popad64();
		a.jmp(0x1402C6DE8);

		a.bind(return_unhandled);
		a.popad64();
		a.jmp(0x1402C64EE);
	}

	int net_compare_base_address(const game::netadr_s* a1, const game::netadr_s* a2)
	{
		if (a1->type == a2->type)
		{
			switch (a1->type)
			{
			case game::netadrtype_t::NA_BOT:
			case game::netadrtype_t::NA_LOOPBACK:
				return a1->port == a2->port;

			case game::netadrtype_t::NA_IP:
				return !memcmp(a1->ip, a2->ip, 4);
			case game::netadrtype_t::NA_BROADCAST:
				return true;
			default:
				break;
			}
		}

		return false;
	}

	int net_compare_address(const game::netadr_s* a1, const game::netadr_s* a2)
	{
		return net_compare_base_address(a1, a2) && a1->port == a2->port;
	}
}

void network::on(const std::string& command, const callback& callback)
{
	get_callbacks()[command] = callback;
}

void network::send(const game::netadr_s& address, const std::string& command, const std::string& data)
{
	std::string packet = "\xFF\xFF\xFF\xFF";
	packet.append(command);
	packet.push_back(' ');
	packet.append(data);

	network::send(address, packet);
}

void network::send(const game::netadr_s& address, const std::string& data)
{
	game::Sys_SendPacket(static_cast<int>(data.size()), data.data(), &address);
}

bool network::are_addresses_equal(const game::netadr_s& a, const game::netadr_s& b)
{
	return net_compare_address(&a, &b);
}

void network::post_unpack()
{
	if (game::environment::is_sp())
	{
		return;
	}

	// redirect dw_sendto to raw socket
	utils::hook::jump(0x140501AAA, reinterpret_cast<void*>(0x140501A3A));

	// intercept command handling
	utils::hook::jump(0x1402C64CB, utils::hook::assemble(handle_command_stub), true);

	utils::hook::jump(0x14041D010, net_compare_address);
	utils::hook::jump(0x14041D060, net_compare_base_address);

	// don't establish secure conenction
	utils::hook::set<uint8_t>(0x1402ECF1D, 0xEB);
	utils::hook::set<uint8_t>(0x1402ED02A, 0xEB);
	utils::hook::set<uint8_t>(0x1402ED34D, 0xEB);
	utils::hook::set<uint8_t>(0x1402C4A1F, 0xEB); //

	// ignore unregistered connection
	utils::hook::jump(0x140471AAC, reinterpret_cast<void*>(0x140471A50));
	utils::hook::set<uint8_t>(0x140471AF0, 0xEB);

	// disable xuid verification
	utils::hook::set<uint8_t>(0x140154AA9, 0xEB);
	utils::hook::set<uint8_t>(0x140154AC3, 0xEB);

	// disable xuid verification
	utils::hook::nop(0x140474584, 2);
	utils::hook::set<uint8_t>(0x1404745DB, 0xEB);

	// ignore configstring mismatch
	utils::hook::set<uint8_t>(0x1402CCCC7, 0xEB);

	// increase cl_maxpackets
	utils::hook::set<uint8_t>(0x1402C8083, 125);
	utils::hook::set<uint8_t>(0x1402C808C, 125);

	// ignore impure client
	utils::hook::jump(0x140472671, reinterpret_cast<void*>(0x1404726F9));
}

REGISTER_MODULE(network)
