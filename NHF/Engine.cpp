#include "Engine.hpp"


sf::Color Engine::initColor(const sf::Vector2f& point, float radius2) {
	float a = point.x - _origin.x;
	float b = point.y - _origin.y;
	float a2b2 = a * a + b * b;

	int transparency_lower_limit = 15;
	int transparency_range = 255 - transparency_lower_limit;
	radius2 = powf(radius2, 1.f / transparency_range);
	float const r_radius2 = radius2;
	float transparency = powf(transparency_range, 1.f / static_cast<float>(transparency_range));
	float const r_transparency = transparency;

	for (int i = 0; i < transparency_range; i++) {
		if (a2b2 < radius2)
			return { 255, 50, 255, static_cast<sf::Uint8>(transparency + transparency_lower_limit) };
		radius2 *= r_radius2;
		transparency *= r_transparency;
	}

	return { 255, 50, 255, static_cast<sf::Uint8>(transparency_range) };
}


Engine::Engine(const sf::Vector2i& window) :
	_window{window},
	_origin{sf::Vector2f{window / 2}}
{
	size_t size = static_cast<size_t>(_window.x) * static_cast<size_t>(_window.y);

	_angleMap.resize(size);
	for (int x = 0; x < _window.x; x++)
		for (int y = 0; y < _window.y; y++) {
			int index = static_cast<size_t>(x * _window.y + y);
			_angleMap[index] = math::calcAngle(sf::Vector2f{ sf::Vector2i{x, y} - sf::Vector2i{ _window.x / 2, _window.y / 2} });
		}

	sf::VertexArray screen{ sf::Points, size };
	_colorPicker.resize(size);
	for (size_t x = 0; x < window.x; x++)
		for (size_t y = 0; y < window.y; y++) {
			size_t index = x * static_cast<size_t>(window.y) + y;
			screen[index].position = { static_cast<float>(x), static_cast<float>(y) };
			_colorPicker[index] = initColor(screen[index].position, static_cast<float>(window.x * window.x / 4 + window.y * window.y / 4));
		}
}
Engine::Engine(const sf::Vector2u& window) : Engine(sf::Vector2i{ window }) {}


Angle Engine::getAngle(const sf::Vector2f& point) const {
	int index = static_cast<int>(point.x) * _window.y + static_cast<int>(point.y);
	return _angleMap[index];
}

sf::Color Engine::getColor(const sf::Vector2f& point) const {
	sf::Vector2i t_point = sf::Vector2i{ point };
	int index = t_point.x * _window.y + t_point.y;
	return _colorPicker[index];
}
