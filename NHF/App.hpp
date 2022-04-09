#pragma once

#include "AppData.hpp"


class App {
private:
	AppData _appData;

	sf::Clock _clock;
	int fps = 60;

public:
	void run();
};
