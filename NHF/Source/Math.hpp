#pragma once

#include <cmath>
#include "SFMLVector2.hpp"
#include "Angle.hpp"


namespace math {
	template <typename T>
	static float square(T num) {
		return static_cast<float>(num * num);
	}

	float calcDistance(const sf::Vector2f& a, const sf::Vector2f& b);

	float calcAngle(const sf::Vector2f& position);
}
