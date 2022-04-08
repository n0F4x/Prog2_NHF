#pragma once

#include "Menu.hpp"
#include "AppData.hpp"
#include "Button.hpp"


class MainMenu : public Menu {
public:
	MainMenu(AppData& appData);

	void handleEvent(const sf::Event& event) override;
};
