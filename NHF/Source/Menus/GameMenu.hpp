#pragma once

#include "Menu.hpp"


class GameMenu : public Menu {
public:
	GameMenu();

	void handleEvent(const sf::Event& event) override;
};

