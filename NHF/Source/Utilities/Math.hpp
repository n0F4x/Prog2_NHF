#pragma once

#include <cmath>
#include <SFML/Graphics.hpp>
#include "Math/Angle.hpp"


namespace math {
	float calcAngle(const sf::Vector2f& position);

	std::vector<sf::Vector2f> getArcPoints(float angle, float spread, float radius, int maxpts);
}
