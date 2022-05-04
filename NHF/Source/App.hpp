#pragma once

#include "AppData.hpp"
#include "Controller.hpp"
#include "Window.hpp"


class App {
private:
	AppData _appData;
	Window _window;
	Controller _controller{_window};

	void init(bool renderPreview = false);

public:
	void run();
};
