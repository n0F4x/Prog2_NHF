#pragma once

#include "Menu.hpp"
#include "GameMenu/Track.hpp"
#include "GameMenu/Player.hpp"


/**
 * @brief	Class for managing the track in the main menu's background
*/
class TrackAI : public Track {
public:
	/**
	 * @brief	Overrides the Track's handleEvent() so that it does not reflect user input
	 * @param	User input
	*/
	void handleEvent(const sf::Event&) override { /* AI only */ }
};
/**
 * @brief	Class for managing the player in the main menu's background
*/
class PlayerAI : public Player {
public:
	/**
	 * @brief	Starts the jumping process of the player
	*/
	void jump() { startJump(); }
	/**
	 * @brief	Overrides the Player's handleEvent so that it does not reflect user input
	 * @param	User input
	*/
	void handleEvent(const sf::Event&) override { /* AI only */ }
};
/**
 * @brief	Class for drawing a dark filter, making the contents in the background easy to distinguish opposed to the main contents of the menu
*/
class Shader : public MenuItem {
	sf::RectangleShape _item{ Window::getSize() };
	/**
	 * @brief	Draws the filter to the render target
	 * @param target	The render target
	 * @param states	The render states
	*/
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override { target.draw(_item); }
public:
	/**
	 * @brief	Constructs a new Shader
	*/
	Shader() { _item.setFillColor({ 0, 0, 0, 220 }); }
};


/**
 * @brief	Class for managing and displaying the main menu of the application
*/
class MainMenu : public Menu {
private:
	// Background
	TrackAI* _track;
	PlayerAI* _player;

public:
	/**
	 * @brief	Constructs a new MainMenu
	*/
	MainMenu();

	/**
	 * @brief	Handles user input inside the main menu
	 * @param event	The user input
	*/
	void handleEvent(const sf::Event& event) override;
	/**
	 * @brief	Updates the states of the main menu
	*/
	void update() override;
};
