#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "../../Utilities/Math/Math.hpp"
#include "../../Utilities/Math/PolarVector.hpp"
#include "../../GUI/Theme.hpp"

struct cmpVector2i {
	bool operator()(const sf::Vector2i& lhs, const sf::Vector2i& rhs) const {
		if (lhs.x != rhs.x) return lhs.x < rhs.x;
		return lhs.y < rhs.y;
	}
};

class PreCalculator {
private:
	sf::Vector2i _window;
	sf::Vector2i _origin;

	std::map<sf::Vector2i, PolarVector, cmpVector2i> _polarVectorMap;
	std::map<sf::Vector2i, sf::Color, cmpVector2i> _colorMap;

	sf::Color initColor(const sf::Vector2i& point, float radius2);

public:
	PreCalculator(const sf::Window& window);

	const PolarVector& getPolarVector(const sf::Vector2f& vector) const {
		return _polarVectorMap.at(sf::Vector2i{ vector });
	}
	const sf::Color& getColor(const sf::Vector2f& point) const {
		if (_colorMap.find(sf::Vector2i{ point }) == _colorMap.end()) {
			return _colorMap.begin()->second;
		}
		return _colorMap.at(sf::Vector2i{ point });
	}
};

