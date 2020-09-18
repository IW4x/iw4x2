#pragma once
#include "loader/module_loader.hpp"

class quick_patch final : public module
{
public:
	quick_patch();

	void post_unpack() override;
private:

};
