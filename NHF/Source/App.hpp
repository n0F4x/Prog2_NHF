#pragma once

#include "AppData.hpp"
#include "Controller.hpp"
#include "Window.hpp"


class App {
private:
	AppData _appData;
	Window _window;
	Controller _controller;

	sf::Clock _clock;
	int fps = 60;

	void init();

public:
	void run();
};
