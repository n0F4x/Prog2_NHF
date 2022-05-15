#pragma once

#include "Core/AppData.hpp"
#include "Core/Controller.hpp"
#include "Core/Window.hpp"

/*! \mainpage BLank text
*
*/

/**
 * @brief	Class for holding the application together
*/
class App {
private:
	AppData _appData;
	Window _window;
	Controller _controller{_window};

	/**
	 * @brief	Initializes the application in the beginning of the process
	 * @param renderPreview	True if a loading screen needs to be rendered
	*/
	void init(bool renderPreview = false);

public:
	/**
	 * @brief	Runs the application's processes
	*/
	void run();
};
