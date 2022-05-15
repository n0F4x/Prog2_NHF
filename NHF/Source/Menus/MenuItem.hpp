#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "../Core/AppData.hpp"
#include "../Core/Window.hpp"
#include "../Utilities/Math/Transitions.hpp"


/**
 * @brief	Abstract class for managing content inside the menus. Capable of managing the contents transitions
*/
class MenuItem : public sf::Drawable {
private:
	bool _isPaused = false;

	std::vector<Transition*> _transitions;

protected:
	/**
	 * @brief	Checks whether the managed content is in paused mode
	 * @return	True if it is paused
	*/
	bool isPaused() const { return _isPaused; }

	/**
	 * @brief	Adds a transition to the MenuItem for management
	 * @param transition	The transition
	*/
	void addTransition(Transition* transition) { _transitions.push_back(transition); }

public:
	/**
	 * @brief	Constructs a new MenuItem
	*/
	MenuItem() = default;
	/**
	 * @brief	Constructs a new MenuItem and adds transition to it for management
	 * @param transitions	The transitions for management
	*/
	explicit MenuItem(const std::vector<Transition*>& transitions) : _transitions{transitions} {}

	/**
	 * @brief	Virtual function for making the class compatible with the Menu class
	*/
	virtual void handleEvent(const sf::Event& event) { /*not pure*/ }
	/**
	 * @brief	Updates the managed transitions
	*/
	virtual void update();
	/**
	 * @brief	Initializes the managed transitions and sets the paused flag to false
	*/
	virtual void init();
	/**
	 * @brief	Pauses the managed transitions and sets the paused flag to true
	*/
	virtual void pause();
	/**
	 * @brief	Resumes the managed transitions and sets the paused flag to false
	*/
	virtual void resume();
};

