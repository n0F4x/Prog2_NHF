#include <cstdlib>
#include "Track.hpp"
#include "Math.hpp"


void Track::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(_screen, states);
}


Track::Track(sf::Window& window) :
	_window{ window },
	_preCalc{ window },
	//_screen{ sf::Points, static_cast<size_t>(window.getSize().x) * static_cast<size_t>(window.getSize().y) },
	_screen{ _preCalc },
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
	}
}

void Track::update() {
	if (!_isPaused) {
		_platforms.update();

		if (_isDragged) {
			sf::Vector2f mouse = sf::Vector2f{ sf::Mouse::getPosition(_window) };

			size_t index = static_cast<size_t>(mouse.x) * _window.getSize().y + static_cast<size_t>(mouse.y);
			size_t index2 = static_cast<size_t>(_mouse.x) * _window.getSize().y + static_cast<size_t>(_mouse.y);

			_platforms.rotate(_preCalc.getPolarVector(index).angle - _preCalc.getPolarVector(index2).angle);
			_mouse = mouse;
		}

		//_screen.clear();
		//auto platform = _platforms.getList().begin();
		//for (auto it = _preCalc.getCircularVectorMap().begin(); it != _preCalc.getCircularVectorMap().end() && platform != _platforms.getList().end(); ++it) {
		//	if (it->first > platform->getOuterRadius()) {
		//		++platform;
		//	}

		//	for (size_t index : it->second) {
		//		if (math::isBetween(_preCalc.getPolarVector(index).angle, platform->getRotation(), platform->getRotation() + platform->getWidth())) {
		//			_screen.append(sf::Vertex{ {static_cast<float>(index) / _window.getSize().y, static_cast<float>(index % _window.getSize().y), }, _preCalc.getColor(index) });
		//		}
		//	}
		//}
		_screen.update(_platforms);
	}
}

void Track::init() {
	_screen.init();
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
