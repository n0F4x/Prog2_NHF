#pragma once

#include "AppData.hpp"
#include "Controller.hpp"
#include "Window.hpp"

class App {
private:
	Controller _controller;

	void init();

public:
	void run();
};
