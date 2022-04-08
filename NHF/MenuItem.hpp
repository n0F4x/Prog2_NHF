#pragma once

#include <SFML/Graphics.hpp>


class MenuItem : public sf::Drawable {
protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

public:
	virtual void handleEvent(const sf::Event& event) {}
	virtual void update() {}
};

