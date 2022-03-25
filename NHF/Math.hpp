#pragma once

#include <cmath>
#include <SFML/Graphics.hpp>
#include "Angle.hpp"


namespace math {
	static Angle calcAngle(const sf::Vector2f& position) {
		if (position.x == 0)
			if (position.y >= 0)	return 90_deg;
			else					return 270_deg;

		if (position.x > 0)
			if (position.y > 0)		return atanf(position.y / position.x);
			else					return atanf(position.y / position.x) + 360_deg;
		else
			return atanf(position.y / position.x) + 180_deg;
	}

	static bool isBetween(Angle angle, Angle min, Angle max) {
		if (max >= 360_deg)
			return angle <= max - 360_deg || angle >= min;
		return angle >= min && angle <= max;
	}

	static void rotate(sf::Vector2f& point, const sf::Vector2f& origin, Angle angle) {
		float a = point.x - origin.x;
		float b = point.y - origin.y;

		float _sin = sin(angle);
		float _cos = cos(angle);

		point.x = a * _cos - b * _sin + origin.x;
		point.y = a * _sin + b * _cos + origin.y;
	}

	static bool isInsideCircle(sf::Vector2f center, float radius, sf::Vector2f point) {
		float a = point.x - center.x;
		float b = point.y - center.y;
		return a * a + b * b <= radius * radius;
	}

	static bool isBetween(sf::Vector2f center, float innerRadius, float outerRadius, sf::Vector2f point) {
		float a = point.x - center.x;
		float b = point.y - center.y;
		float a2_b2 = a * a + b * b;
		return a2_b2 <= outerRadius * outerRadius && a2_b2 >= innerRadius * innerRadius;
	}
}
