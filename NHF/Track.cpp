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

//void Track::switchLane() {
//	if (_switchDirection != 0) {
//		if (_rotationSpeed >= _maxRotationSpeed || _rotationSpeed <= _maxRotationSpeed * -1) {
//			_switchDirection = 0 - _switchDirection;
//		}
//
//		_rotationSpeed += _rotationAcc * _switchDirection;
//		rotate(_rotationSpeed);
//
//		if (_rotationSpeed * _switchDirection <= 0) {
//			_switchDirection = 0;
//		}
//	}
//}


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
	_mouse{ mouse }
{
	Platform::setOrigin(sf::Vector2f{ window.getSize() / 2u });
	Platform::setScale(_scaleSpeed);


	size_t size = static_cast<size_t>(window.getSize().x) * static_cast<size_t>(window.getSize().y);
	_screen = sf::VertexArray{ sf::Points, size };

	for (size_t x = 0; x < window.getSize().x; x++)
		for (size_t y = 0; y < window.getSize().y; y++) {
			size_t index = x * static_cast<size_t>(window.getSize().y) + y;
			_screen[index].position = { static_cast<float>(x), static_cast<float>(y) };
		}


	_platforms.emplace_front();
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

	//if (event.type == sf::Event::KeyPressed) {
	//	if (event.key.code == sf::Keyboard::Right)
	//		_switchDirection = 1;
	//	if (event.key.code == sf::Keyboard::Right)
	//		_switchDirection = -1;
	//}

	if (_isDragged) {
		sf::Vector2f mouse = sf::Vector2f{ sf::Mouse::getPosition(_window) };

		size_t index = static_cast<size_t>(mouse.x) * _window.getSize().y + static_cast<size_t>(mouse.y);
		size_t index_ = static_cast<size_t>(_mouse.x) * _window.getSize().y + static_cast<size_t>(_mouse.y);

		rotate(_engine.getPolarVector(index).angle - _engine.getPolarVector(index_).angle);
		setMouse(mouse);
	}
}

void Track::update() {
	updatePlatforms();

	auto platform = _platforms.begin();
	for (auto it = _engine.getCircularVectorMap().begin(); it != _engine.getCircularVectorMap().end() && platform != _platforms.end(); ++it) {
		if (it->first > platform->getOuterRadius()) {
			++platform;
		}

		for (size_t index: it->second) {
			if (math::isBetween(_engine.getPolarVector(index).angle, platform->getRotation(), platform->getRotation() + platform->getWidth())) {
				_screen[index].color = _engine.getColor(index);
			}
			else {
				_screen[index].color = sf::Color::Transparent;
			}
		}
	}
}
