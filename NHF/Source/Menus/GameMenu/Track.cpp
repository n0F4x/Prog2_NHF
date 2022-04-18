#include "Track.hpp"


void Track::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(_platforms);
}


Track::Track() :
	_platforms{ _preCalc },
	_mouse{ sf::Vector2f{sf::Mouse::getPosition(_window())} }
{}


void Track::handleEvent(const sf::Event& event) {
	if (!_isPaused) {
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				_mouse = sf::Vector2f{ sf::Mouse::getPosition(_window()) };
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
			sf::Vector2f mouse = sf::Vector2f{ sf::Mouse::getPosition(_window()) };

			_platforms.rotate(_preCalc.getPolarVector(mouse).angle - _preCalc.getPolarVector(_mouse).angle);
			_mouse = mouse;
		}

		if (_switchingLeft != _switchingRight) {
			if (_switchingLeft) {
				_transition.start({ -1 * Platform::width, 0.f }, 100);
			}
			if (_switchingRight) {
				_transition.start({ Platform::width, 0.f }, 100);
			}
		}

		_transition.update();

		_platforms.update();
	}
}

void Track::init() {
	_platforms.init();
	_transition.init();

	_isDragged = false;
}

void Track::pause() {
	_isPaused = true;
}

void Track::resume() {
	_mouse = sf::Vector2f{ sf::Mouse::getPosition(_window()) };

	_isPaused = false;
}
