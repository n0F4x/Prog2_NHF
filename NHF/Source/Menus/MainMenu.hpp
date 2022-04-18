#pragma once

#include "Menu.hpp"


class MainMenu : public Menu {
public:
	MainMenu();

	void handleEvent(const sf::Event& event) override;
};
