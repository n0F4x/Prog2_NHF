#pragma once

#include "../Menu.hpp"
#include "../../AppData/AppData.hpp"


class InitMenu : public Menu {
public:
	InitMenu(AppData& appData);

	void update() override;
};

