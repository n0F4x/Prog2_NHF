#pragma once

#include <vector>
#include "Math.hpp"


class Engine {
private:
	Engine(const sf::Vector2i& window);
	sf::Vector2i _window;
	sf::Vector2f _origin;

	std::vector<Angle> _angleMap;
	std::vector<sf::Color> _colorPicker;

	sf::Color initColor(const sf::Vector2f& point, float radius2);

public:
	Engine() = default;
	Engine(const sf::Vector2u& window);

	Angle getAngle(const sf::Vector2f& point) const;
	sf::Color getColor(const sf::Vector2f& point) const;
};

