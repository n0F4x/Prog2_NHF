#pragma once

#include <string>
#include <SFML/Graphics.hpp>

class Controller;


/**
 * @brief Abstract Menu class. 
		Manages state of Menu that can be accessed by the Controller class.
		This state is used to inform the controller when it needs to switch to a different menu or close the application
*/
class MenuBase {
private:
	friend Controller;
	bool __isExiting__ = false;
	bool __isClosing__ = false;
	bool __openLast__ = false;
	std::string __next__;

	/**
	 * @brief	Resets state of class
	*/
	void __init__() {
		__isClosing__ = false;
		__openLast__ = false;
		__next__.clear();
	}

protected:
	/**
	 * @brief	Sets state to represent the next menu to be opened
	 * @param next	Name of the next menu to be opened
	*/
	void open(const std::string_view& next) { __next__ = next; }
	/**
	 * @brief	Sets "__openLast__" flag to true. Class will inform the controller that the last visited menu needs to be opened
	*/
	void openLast() { __openLast__ = true; }
	/**
	 * @brief	Sets "__isClosing__" flag to true. Class will inform the controller that the current menu needs to be closed
	*/
	void close() { __isClosing__ = true; }
	/**
	 * @brief	Sets "__isExiting__" flag to true. Class will inform the controller that the application has to exit
	*/
	void exit() { __isExiting__ = true; }

public:
	/**
	 * @brief	Pure virtual for handling user input
	 * @param event	User input
	*/
	virtual void handleEvent(const sf::Event& event) = 0;
	/**
	 * @brief	Pure virtual for refreshing the backend of the menu
	*/
	virtual void update() = 0;
	/**
	 * @brief	Pure virtual for refreshing the view
	*/
	virtual void render() = 0;

	/**
	 * @brief	Pure virtual for initializing the backend of the menu
	*/
	virtual void init() = 0;
	/**
	 * @brief	Pure virtual for pausing the menu
	*/
	virtual void pause() = 0;
	/**
	 * @brief	Pure virtual for resuming the menu
	*/
	virtual void resume() = 0;

	/**
	 * @brief	Default virtual desctructor
	*/
	virtual ~MenuBase() = default;
};
