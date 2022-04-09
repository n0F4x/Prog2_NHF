#include "PreCalculator.hpp"


sf::Color PreCalculator::initColor(const sf::Vector2f& point, float radius2) {
	float a = point.x - _origin.x;
	float b = point.y - _origin.y;
	float a2b2 = a * a + b * b;

	int transparency_lower_limit = 0;
	int transparency_range = 220 - transparency_lower_limit;
	radius2 = powf(radius2, 1.f / transparency_range);
	float const r_radius2 = radius2;
	float transparency = powf(static_cast<float>(transparency_range), 1.f / static_cast<float>(transparency_range));
	float const r_transparency = transparency;

	for (int i = 0; i < transparency_range; i++) {
		if (a2b2 < radius2)
			return { 255, 50, 255, static_cast<sf::Uint8>(transparency + transparency_lower_limit) };
		radius2 *= r_radius2;
		transparency *= r_transparency;
	}

	return { 255, 50, 255, static_cast<sf::Uint8>(transparency_range) };
}


PreCalculator::PreCalculator(const sf::Window& window) :
	_window{window.getSize()},
	_origin{_window / 2u}
{
	size_t size = static_cast<size_t>(_window.x) * static_cast<size_t>(_window.y);

	_polarVectorMap.resize(size);
	_colorPicker.resize(size);

	std::map<int, std::vector<sf::Vector2f>> circularVectorMap;

	for (size_t x = 0; x < _window.x; x++) {
		for (size_t y = 0; y < _window.y; y++) {
			size_t index = x * static_cast<size_t>(_window.y) + y;

			sf::Vector2f point = { static_cast<float>(x), static_cast<float>(y) };
			float radius = sqrt((point - _origin).x * (point - _origin).x + (point - _origin).y * (point - _origin).y);

			_polarVectorMap.at(index) = { radius, math::calcAngle(point - _origin) };
			_colorPicker.at(index) = initColor(point, _origin.x * _origin.x + _origin.y * _origin.y);

			circularVectorMap[static_cast<int>(radius * radius)].emplace_back(point);
		}
	}


	for (auto it : circularVectorMap) {
		_circularVectorMap.emplace_back(std::make_pair<float, std::vector<size_t>>(static_cast<float>(sqrt(it.first)), {}));
		for (auto v : it.second) {
			_circularVectorMap.back().second.emplace_back(static_cast<size_t>(v.x) * _window.y + static_cast<size_t>(v.y));
		}
	}
}
