#pragma once

#include <map>
#include <SFML/Graphics.hpp>
#include "../../Utilities/Math/PolarVector.hpp"


class PreCalculator {
private:
	struct cmpVector2i { bool operator()(const sf::Vector2i& lhs, const sf::Vector2i& rhs) const; };
	std::map<sf::Vector2i, PolarVector, cmpVector2i> _polarVectorMap;

public:
	PreCalculator();

	const PolarVector& getPolarVector(const sf::Vector2f& vector) const {
		return _polarVectorMap.at(sf::Vector2i{ vector });
	}
};
