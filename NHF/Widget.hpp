#pragma once

#include <SFML/Graphics.hpp>


class Widget : public sf::Drawable {
protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

public:
	virtual void update() = 0;
};

