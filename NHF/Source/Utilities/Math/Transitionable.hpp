#pragma once


/**
 * @brief	Abstract class for making objects compatible with the Transition class
*/
class Transitionable {
public:
	virtual void transition(const sf::Vector2f& amount) = 0;
};
