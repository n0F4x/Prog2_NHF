#include "Math.hpp"


namespace math {
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
			const float a = (angle - spread / 2.f) + (i * spread) / (maxpts - 1);
			pts.emplace_back(radius * sf::Vector2f{ cosf(a), sinf(a) });
		}
		return pts;
	}
}