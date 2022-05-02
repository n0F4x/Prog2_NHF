#include "Math.hpp"


namespace math {
	float calcDistance(const sf::Vector2f& a, const sf::Vector2f& b) {
		return sqrtf(square(a.x - b.x) + square(a.y - b.y));
	}

	float calcAngle(const sf::Vector2f& position) {
		if (position.x == 0) {
			if (position.y >= 0) {
				return 90_deg;
			}
			else {
				return 270_deg;
			}
		}
		else {
			if (position.x > 0) {
				if (position.y > 0) {
					return atanf(position.y / position.x);
				}
				else {
					return atanf(position.y / position.x) + 360_deg;
				}
			}
			else {
				return atanf(position.y / position.x) + 180_deg;
			}
		}
	}
}
