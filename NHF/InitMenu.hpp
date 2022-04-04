#pragma once

#include "AppData.hpp"


class InitMenu : public Menu {
private:
	AppData& _appData;

	sf::Text _text;

public:
	InitMenu(AppData& appData);

	void handleEvent(const sf::Event&);
	void update();
	void render();
};

