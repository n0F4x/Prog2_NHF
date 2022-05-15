#pragma once

#include "../../Menus/MenuItem.hpp"
#include "PreCalculator.hpp"
#include "../../Utilities/Math/Transitions.hpp"
#include "PlatformContainer.hpp"


/**
 * @brief	Class for managing the playing field of the game
*/
class Track : public MenuItem {
private:
	// "Observables"
	PreCalculator _preCalc;
	Transitions::EaseInOut _transition{ &_platforms };

	// Managed items
	PlatformContainer _platforms{ _preCalc };
	sf::VertexArray _shader{ sf::TriangleFan };

	// Variables
	sf::Vector2f _mouse{ sf::Vector2f{sf::Mouse::getPosition(Window::window())} };
	bool _isDragged = false;
	int _switchingState = 0;
	bool _switchingLeft = false;
	bool _switchingRight = false;

	/**
	 * @brief	Helper function for switchLanes(). Starts the switching transition
	 * @param direction	The direction of the transition
	*/
	void switchLane(float direction);
	/**
	 * @brief	Performs lane switching
	*/
	void switchLanes();

	// Contexts
	unsigned _laneCount = 8u;
	ContextRepr<unsigned> _platformSpeed{ AppData::findContext("speed") };
	ContextRepr<PlatformControl> _platformControl{ AppData::findContext("platformControl") };
	ContextRepr<sf::Event::KeyEvent> _switchKey1{ AppData::findContext("switchKey1") };
	ContextRepr<sf::Event::KeyEvent> _switchKey2{ AppData::findContext("switchKey2") };
	ContextRepr<bool> _holdSwitch{ AppData::findContext("holdSwitch") };

protected:
	/**
	 * @brief	Draws the playing field to the render target
	 * @param target	The render target
	 * @param states	The render states
	*/
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	/**
	 * @brief	Handles mouse events
	 * @param mouseEvent	The mouse event to be handled
	*/
	void handleMouseEvent(const sf::Event& mouseEvent);
	/**
	 * @brief	Handles key events
	 * @param mouseEvent	The key event to be handled
	*/
	void handleKeyEvent(const sf::Event& keyEvent);

public:
	/**
	 * @brief	Constructs a new Track
	*/
	Track();

	/**
	 * @brief	Checks whether a point is on one of the platforms inside the playing field
	 * @param point	The point in question
	 * @return	True if it is on a platform
	*/
	bool isOnPlatforms(const sf::Vector2f& point) const;
	/**
	 * @brief	Helper function for the background algorithm inside the main menu
	 * @param playerFeet	The coordinates of the player's feet
	 * @return	True if the player needs to jump
	*/
	bool AI_jump(const sf::Vector2f& playerFeet);

	/**
	 * @brief	Handles user input
	 * @param event	The user input
	*/
	void handleEvent(const sf::Event& event) override;
	/**
	 * @brief	Updates the state of the playing field
	*/
	void update() override;
	/**
	 * @brief	Initializes the states of the playing field
	*/
	void init() override;
	/**
	 * @brief	Sets the state of the Track to resumed
	*/
	void resume() override;
};
