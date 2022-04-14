#include "PreCalculator.hpp"


sf::Color PreCalculator::initColor(const sf::Vector2i& point, float radius2) {
	float a = static_cast<float>(point.x) - _origin.x;
	float b = static_cast<float>(point.y) - _origin.y;
	float a2b2 = a * a + b * b;

	int transparency_lower_limit = 0;
	int transparency_range = 220 - transparency_lower_limit;
	radius2 = powf(radius2, 1.f / transparency_range);
	float const r_radius2 = radius2;
	float transparency = powf(static_cast<float>(transparency_range), 1.f / static_cast<float>(transparency_range));
	float const r_transparency = transparency;

	sf::Color res{ theme::Purple };
	for (int i = 0; i < transparency_range; i++) {
		if (a2b2 < radius2) {
			res.a = static_cast<sf::Uint8>(transparency + transparency_lower_limit);
			return res;
		}
		radius2 *= r_radius2;
		transparency *= r_transparency;
	}

	res.a = static_cast<sf::Uint8>(transparency_range);
	return res;
}


PreCalculator::PreCalculator(const sf::Window& window) :
	_window{ window.getSize() },
	_origin{ _window / 2 }
{
	for (int x = 0; x < _window.x; x++) {
		for (int y = 0; y < _window.y; y++) {
			sf::Vector2i point{ x, y };
			float radius = static_cast<float>(sqrt((point - _origin).x * (point - _origin).x + (point - _origin).y * (point - _origin).y));

			_polarVectorMap[point] = { radius, math::calcAngle(sf::Vector2f{point - _origin}) };
			_colorMap[point] = initColor(point, static_cast<float>(_origin.x * _origin.x + _origin.y * _origin.y));
		}
	}
}
