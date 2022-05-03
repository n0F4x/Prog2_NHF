#pragma once

#include <cmath>
#include <SFML/Graphics.hpp>
#include "Math/Angle.hpp"


namespace math {
	template <typename T>
	T square(T num) {
		return num * num;
	}
	inline float squaref(float num) {
		return num * num;
	}

	float calcDistance(const sf::Vector2f& a, const sf::Vector2f& b);

	float calcAngle(const sf::Vector2f& position);

	std::vector<sf::Vector2f> getArcPoints(float angle, float spread, float radius, int maxpts);
}
