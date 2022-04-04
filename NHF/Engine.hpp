#pragma once

#include <vector>
#include "Math.hpp"
#include "PolarVector.hpp"


class Engine {
private:
	Engine(const sf::Vector2i& window);
	sf::Vector2i _window;
	sf::Vector2f _origin;

	std::vector<PolarVector> _polarVectorMap;
	std::vector<std::pair<float, std::vector<size_t>>> _circularVectorMap;	// Pair = <radius, points_with_same_radius>
	std::vector<sf::Color> _colorPicker;

	sf::Color initColor(const sf::Vector2f& point, float radius2);

public:
	Engine() = default;
	Engine(const sf::Vector2u& window);

	void init();

	const PolarVector& getPolarVector(size_t index) const {
		return _polarVectorMap[index];
	}
	const sf::Color& getColor(size_t index) const {
		return _colorPicker[index];
	}
	const std::vector<std::pair<float, std::vector<size_t>>>& getCircularVectorMap() const {
		return _circularVectorMap;
	}
};
