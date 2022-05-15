#pragma once

#include <memory>
#include "../Utilities/STL/vector.hpp"
#include "../Core/Controller/MenuBase.hpp"
#include "../Core/AppData.hpp"
#include "../Core/Window.hpp"
#include "MenuItem.hpp"


/**
 * @brief	Base class for the menus inside the application. Capable of holding MenuItems, making it easy to manage them
*/
class Menu : public MenuBase {
private:
	util::vector<std::unique_ptr<MenuItem>> _items;

	bool _isPaused = false;

protected:
	/**
	 * @brief	Adds a MenuItem to be managed
	 * @param item	The MenuItem
	*/
	void addMenuItem(std::unique_ptr<MenuItem> item);

	/**
	 * @brief	Gets the paused flag of the menu
	 * @return	True of the menu is currently in paused mode
	*/
	bool isPaused() const { return _isPaused; }

public:
	/**
	 * @brief	Handles the user input for the managed items
	 * @param event	The user input
	*/
	void handleEvent(const sf::Event& event) override;
	/**
	 * @brief	Updates the managed items
	*/
	void update() override;
	/**
	 * @brief	Renders the managed items to the screen
	*/
	void render() override;
	
	/**
	 * @brief	Initializes the state of the menu and the managed items
	*/
	void init() override;
	/**
	 * @brief	Pauses the menu and the managed items
	*/
	void pause() override;
	/**
	 * @brief	Resumes the menu and the managed items
	*/
	void resume() override;
};
