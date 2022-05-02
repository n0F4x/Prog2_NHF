#pragma once

#include "Menu.hpp"


class MainMenu : public Menu {
public:
	void handleEvent(const sf::Event& event) override;
};
