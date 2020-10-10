#pragma once
#include "loader/module_loader.hpp"

class logs final : public module
{
public:
	struct game_console
	{
	public:
		static void log(const char* message, ...);
		static bool save();

	private:
		static std::string buffer;
	};

private:
	
	void pre_destroy() override;
	static std::string get_log_time();
};
