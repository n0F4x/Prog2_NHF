#pragma once

#include "Core/AppData.hpp"
#include "Core/Controller.hpp"
#include "Core/Window.hpp"


class App {
private:
	AppData _appData;
	Window _window;
	Controller _controller{_window};

	void init(bool renderPreview = false);

public:
	void run();
};
