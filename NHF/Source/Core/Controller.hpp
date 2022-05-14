#pragma once

#include "Controller/MenuNode.hpp"
#include "Window.hpp"


class App;


/**
 * @brief	Class for managing menus
*/
class Controller {
private:
	MenuNode _root;

	MenuNode* _current = nullptr;

	void open();
	void openLast();
	void close();

	Window& _window;
	bool _preview = false;

public:
	/**
	 * @brief	Constructs new empty Controller
	 * @param window	The window of the application
	*/
	explicit Controller(Window& window);

	/**
	 * @brief	Renders a preview. Supposed to be called before load, but not necessary
	*/
	void renderPreview();
	/**
	 * @brief	Builds menu tree
	*/
	void load();

	/**
	 * @brief	Switches the current menu to another based on the its state
	 * @return	True if the menu current menu didn't request the application to be closed
	*/
	bool isActive();

	/**
	 * @brief	Returns pointer to the current menu
	 * @return	Pointer to the current menu
	*/
	MenuBase* operator->() const;
};
