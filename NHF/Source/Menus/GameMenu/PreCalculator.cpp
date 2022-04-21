#include "PreCalculator.hpp"

#include "../../Window.hpp"
#include "../../Utilities/Math.hpp"


PreCalculator::PreCalculator() {
	sf::Vector2i window{ Window::getSize() };
	sf::Vector2i origin{ window / 2 };

	for (int x = 0; x < window.x; x++) {
		for (int y = 0; y < window.y; y++) {
			sf::Vector2i point{ x, y };
			float radius = sqrtf(static_cast<float>((point - origin).x * (point - origin).x + (point - origin).y * (point - origin).y));

			_polarVectorMap[point] = { radius, math::calcAngle(sf::Vector2f{point - origin}) };
		}
	}
}


bool PreCalculator::cmpVector2i::operator()(const sf::Vector2i& lhs, const sf::Vector2i& rhs) const {
	if (lhs.x != rhs.x) return lhs.x < rhs.x;
	return lhs.y < rhs.y;
}
