#pragma once


class Transitionable {
public:
	virtual void transition(const sf::Vector2f amount) = 0;
};
