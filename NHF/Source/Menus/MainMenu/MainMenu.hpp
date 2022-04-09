#pragma once

#include "../Menu.hpp"
#include "../../AppData/AppData.hpp"
#include "../../GUI/Widgets/Button/Button.hpp"


class MainMenu : public Menu {
public:
	MainMenu(AppData& appData);

	void handleEvent(const sf::Event& event) override;
};
