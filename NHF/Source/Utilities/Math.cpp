#include "Math.hpp"


namespace math {
	float calcDistance(const sf::Vector2f& a, const sf::Vector2f& b) {
		return sqrtf(squaref(a.x - b.x) + squaref(a.y - b.y));
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

	std::vector<sf::Vector2f> getArcPoints(float angle, float spread, float radius, int maxpts) {
		std::vector<sf::Vector2f> pts;
		for (int i = 0; i < maxpts; ++i) {
			const float a = (angle - spread / 2.f) + (static_cast<float>(i) * spread) / static_cast<float>(maxpts - 1);
			pts.emplace_back(radius * sf::Vector2f{ cosf(a), sinf(a) });
		}
		return pts;
	}
}
