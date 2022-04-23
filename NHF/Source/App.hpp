#pragma once

#include "Controller.hpp"


class App {
private:
	Controller _controller;

	void init();

public:
	void run();
};
