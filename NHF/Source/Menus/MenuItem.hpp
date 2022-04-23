#pragma once

#include <SFML/Graphics.hpp>


class MenuItem : public sf::Drawable {
public:
	virtual void handleEvent(const sf::Event& event) { /*not pure*/ }
	virtual void update() { /*not pure*/ }
	virtual void init() { /*not pure*/ }
	virtual void pause() { /*not pure*/ }
	virtual void resume() { /*not pure*/ }
};

