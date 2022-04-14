#include <cstdlib>
#include "Track.hpp"
#include "../../Utilities/Math/Math.hpp"


void Track::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(_platforms);
}


Track::Track(sf::Window& window) :
	_window{ window },
	_preCalc{ window },
	_platforms{ window },
	_mouse{ sf::Vector2f{sf::Mouse::getPosition(window)} }
{}


void Track::handleEvent(const sf::Event& event) {
	if (!_isPaused) {
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				_mouse = sf::Vector2f{ sf::Mouse::getPosition(_window) };
				_isDragged = true;
			}
		}
		if (event.type == sf::Event::MouseButtonReleased) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				_isDragged = false;
			}
		}
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Left) {
				_switchingLeft = true;
			}
			if (event.key.code == sf::Keyboard::Right) {
				_switchingRight = true;
			}
		}
		if (event.type == sf::Event::KeyReleased) {
			if (event.key.code == sf::Keyboard::Left) {
				_switchingLeft = false;
			}
			if (event.key.code == sf::Keyboard::Right) {
				_switchingRight = false;
			}
		}
	}
}

void Track::update() {
	if (!_isPaused) {
		if (_isDragged) {
			sf::Vector2f mouse = sf::Vector2f{ sf::Mouse::getPosition(_window) };

			size_t index = static_cast<size_t>(mouse.x) * _window.getSize().y + static_cast<size_t>(mouse.y);
			size_t index2 = static_cast<size_t>(_mouse.x) * _window.getSize().y + static_cast<size_t>(_mouse.y);

			_platforms.rotate(_preCalc.getPolarVector(index).angle - _preCalc.getPolarVector(index2).angle);
			_mouse = mouse;
		}

		if (_switchingLeft != _switchingRight) {
			if (_switchingLeft) _physics.rotate(Direction::NEGATIVE);
			if (_switchingRight) _physics.rotate(Direction::POSITIVE);
		}

		_physics.update(_platforms);

		_platforms.update();
	}
}

void Track::init() {
	_platforms.init();

	_isDragged = false;
}

void Track::pause() {
	_isPaused = true;
}

void Track::resume() {
	_mouse = sf::Vector2f{ sf::Mouse::getPosition(_window) };

	_isPaused = false;
}
