#include <cstdlib>
#include "Track.hpp"
#include "Math.hpp"


void Track::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(_screen, states);
}

bool Track::isInside(const sf::Vector2f& point) const {
	for (const auto& platform : _platforms)
		if (platform.isInside(point))
			return true;
	return false;
}


Track::Track(sf::Window& window, Engine& math, const sf::Vector2f& mouse) :
	_window{ window },
	_engine{ math },
	_origin{ sf::Vector2f{ window.getSize() / 2u } },
	_mouse{ mouse } {
	Platform::setOrigin(_origin);
	Platform::setScale(_scaleSpeed);


	size_t size = static_cast<size_t>(window.getSize().x) * static_cast<size_t>(window.getSize().y);
	_screen = sf::VertexArray{ sf::Points, size };

	for (size_t x = 0; x < window.getSize().x; x++)
		for (size_t y = 0; y < window.getSize().y; y++) {
			size_t index = x * static_cast<size_t>(window.getSize().y) + y;
			_screen[index].position = { static_cast<float>(x), static_cast<float>(y) };
		}

	_platforms.emplace_front(_engine);
}

void Track::rotate(Angle angle) {
	for (auto& platform : _platforms)
		platform.rotate(angle);
	_rotation += angle;
}

void Track::updatePlatforms() {
	_counter++;
	for (auto& platform : _platforms)
		platform.update();

	while (!_platforms.empty() && _platforms.back().isDead()) {
		_platforms.pop_back();
	}

	if (_counter >= _scaleSpeed) {
		_platforms.emplace_front(_engine);
		_platforms.front().rotate((rand() % 12) * 30_deg + _rotation);
		_counter = 0;
	}
}

void Track::setMouse(const sf::Vector2f& mouse) {
	_mouse = mouse;
}

void Track::handleEvent(const sf::Event& event) {
	if (event.type == sf::Event::MouseButtonPressed)
		if (event.mouseButton.button == sf::Mouse::Left) {
			setMouse(sf::Vector2f{ sf::Mouse::getPosition(_window) });
			_isDragged = true;
		}
	if (event.type == sf::Event::MouseButtonReleased)
		if (event.mouseButton.button == sf::Mouse::Left)
			_isDragged = false;

	if (_isDragged) {
		sf::Vector2f mouse = sf::Vector2f{ sf::Mouse::getPosition(_window) };

		rotate(_engine.getAngle(mouse) - _engine.getAngle(_mouse));
		setMouse(mouse);
	}
}

void Track::update() {
	updatePlatforms();

	for (size_t i = 0; i < _screen.getVertexCount(); i++)
		if (isInside(_screen[i].position))
			_screen[i].color = _engine.getColor(_screen[i].position);
		else
			_screen[i].color = sf::Color::Transparent;
}
