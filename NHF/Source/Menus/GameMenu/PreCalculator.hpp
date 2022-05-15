#pragma once

#include <map>
#include <SFML/Graphics.hpp>
#include "../../Utilities/Math/PolarVector.hpp"


/**
 * @brief	Class for performing pre-calculations
*/
class PreCalculator {
private:
	struct cmpVector2i { bool operator()(const sf::Vector2i& lhs, const sf::Vector2i& rhs) const; };
	std::map<sf::Vector2i, PolarVector, cmpVector2i> _polarVectorMap;

public:
	/**
	 * @brief	Constructs a new PreCalculator and performs the calculations
	*/
	PreCalculator();

	/**
	 * @brief	Gets the pre-calculated result of converting a vector given in Descartes coordinates to a polar vector
	 * @param vector	The vector to be converted in Descartes coordinates
	 * @return	The polar result of the conversion
	*/
	const PolarVector& getPolarVector(const sf::Vector2f& vector) const {
		return _polarVectorMap.at(sf::Vector2i{ vector });
	}
};
