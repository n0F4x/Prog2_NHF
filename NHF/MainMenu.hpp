#pragma once

#include "AppData.hpp"
#include "Button.hpp"


class MainMenu : public Menu {
private:
	AppData& _appData;

	Button _PlayButton;

public:
	MainMenu(AppData& appData);

	void handleEvent(const sf::Event& event) override;
	void update() override;
	void render() override;
};

