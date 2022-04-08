#include <cstdlib>
#include "Track.hpp"
#include "Math.hpp"


void Track::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(_screen, states);
}

void Track::rotate(float angle) {
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
		_platforms.emplace_front();
		_platforms.front().rotate((rand() % 12) * 30_deg + _rotation);
		_counter = 0;
	}
}


Track::Track(sf::Window& window, Engine& math, const sf::Vector2f& mouse) :
	_window{ window },
	_engine{ math },
	_mouse{ mouse },
	_screenSize{ static_cast<size_t>(window.getSize().x) * static_cast<size_t>(window.getSize().y) },
	_screen{sf::Points, _screenSize}
{
	Platform::setOrigin(sf::Vector2f{ window.getSize() / 2u });
	Platform::setScale(_scaleSpeed);

	for (size_t x = 0; x < window.getSize().x; x++) {
		for (size_t y = 0; y < window.getSize().y; y++) {
			size_t index = x * static_cast<size_t>(window.getSize().y) + y;
			_screen[index].position = { static_cast<float>(x), static_cast<float>(y) };
		}
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
}

void Track::update() {
	updatePlatforms();

	if (_isDragged) {
		sf::Vector2f mouse = sf::Vector2f{ sf::Mouse::getPosition(_window) };

		size_t index = static_cast<size_t>(mouse.x) * _window.getSize().y + static_cast<size_t>(mouse.y);
		size_t index_ = static_cast<size_t>(_mouse.x) * _window.getSize().y + static_cast<size_t>(_mouse.y);

		rotate(_engine.getPolarVector(index).angle - _engine.getPolarVector(index_).angle);
		setMouse(mouse);
	}

	_screen.clear();
	auto platform = _platforms.begin();
	for (auto it = _engine.getCircularVectorMap().begin(); it != _engine.getCircularVectorMap().end() && platform != _platforms.end(); ++it) {
		if (it->first > platform->getOuterRadius()) {
			++platform;
		}

		for (size_t index : it->second) {
			if (math::isBetween(_engine.getPolarVector(index).angle, platform->getRotation(), platform->getRotation() + platform->getWidth())) {
				_screen.append(sf::Vertex{ {static_cast<float>(index) / _window.getSize().y, static_cast<float>(index % _window.getSize().y), }, _engine.getColor(index) });
			}
		}
	}
}

void Track::init() {
	for (size_t i = 0; i < _screenSize; i++)
		_screen[i].color = sf::Color::Transparent;
	_platforms.clear();
	_platforms.emplace_front();
	_counter = 0;
	_rotation = 0_deg;
	_isDragged = false;
}
