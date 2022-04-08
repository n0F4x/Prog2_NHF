#pragma once

#include "Menu.hpp"
#include "AppData.hpp"
#include "Button.hpp"


class MainMenu : public Menu {
	// std::unique_ptr<Button> _button;

public:
	MainMenu(AppData& appData);

	void handleEvent(const sf::Event& event) override;
	void update() override;
	void render() override;
};
