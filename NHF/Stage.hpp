#pragma once

#include <SFML/Graphics.hpp>


class Stage {
public:
	virtual void handleEvent(const sf::Event& event) = 0;
	virtual void update() = 0;
	virtual void render() = 0;

	virtual void pause() {};
	virtual void resume() {};
};
