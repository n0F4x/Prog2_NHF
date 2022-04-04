#pragma once

#include <cmath>
#include <SFML/Graphics.hpp>
#include "Angle.hpp"


namespace math {
	static float calcAngle(const sf::Vector2f& position) {
		if (position.x == 0)
			if (position.y >= 0)	return 90_deg;
			else					return 270_deg;

		if (position.x > 0)
			if (position.y > 0)		return atanf(position.y / position.x);
			else					return atanf(position.y / position.x) + 360_deg;
		else
			return atanf(position.y / position.x) + 180_deg;
	}

	static bool isBetween(float angle, float min, float max) {
		if (max >= 360_deg)
			return angle <= max - 360_deg || angle >= min;
		return angle >= min && angle <= max;
	}
}
