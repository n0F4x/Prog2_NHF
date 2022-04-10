#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "../../Utilities/Math/Math.hpp"
#include "../../Utilities/Math/PolarVector.hpp"


class PreCalculator {
private:
	sf::Vector2u _window;
	sf::Vector2f _origin;

	std::vector<PolarVector> _polarVectorMap;
	std::vector<std::pair<float, std::vector<size_t>>> _circularVectorMap;	// Pair = <radius, points_with_same_radius>
	std::vector<sf::Color> _colorPicker;

	sf::Color initColor(const sf::Vector2f& point, float radius2);

public:
	PreCalculator(const sf::Window& window);

	const sf::Vector2u& getWindow() const {
		return _window;
	}

	const PolarVector& getPolarVector(size_t index) const {
		return _polarVectorMap[index];
	}
	const sf::Color getColor(size_t index) const {
		if (index >= _colorPicker.size())
			return { 255, 50, 255 };
		return _colorPicker[index];
	}
	const std::vector<std::pair<float, std::vector<size_t>>>& getCircularVectorMap() const {
		return _circularVectorMap;
	}
};

