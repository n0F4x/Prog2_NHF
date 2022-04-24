#pragma once

#include "AppData.hpp"
#include "Controller.hpp"
#include "Window.hpp"


class App {
private:
	AppData _appData;
	Window _window;
	Controller _controller;

	void init();

public:
	void run();
};
