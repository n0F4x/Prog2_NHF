#include "Track.hpp"

#include "../../AppData.hpp"
#include "../../Window.hpp"
#include "../../Utilities/Math.hpp"


void Track::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(_platforms);
	target.draw(_shader);
}


Track::Track() {
	sf::Vector2f origin = { Window::getSize() / 2.f };
	sf::Vertex mid{ origin, sf::Color{ 0, 0, 0, 255 } };
	float radius = sqrtf(origin.x * origin.x + origin.y * origin.y);

	_shader.append(mid);
	for (const sf::Vector2f& v : math::getArcPoints(0.f, 360_deg, radius, 1200)) {
		sf::Vertex point{ origin + v };
		point.color = sf::Color{ 0, 0, 0, 0 };
		_shader.append(point);
	}
	_shader.append(mid);

	addTransition(&_transition);
}


bool Track::isOnPlatform(const sf::Vector2f& point) const { /*TODO*/
	return false;
}


void Track::handleEvent(const sf::Event& event) {
	if (!isPaused()) {
		if (AppData::context.getPlatformControl().first == PlatformControl::Mouse) {
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					_mouse = sf::Vector2f{ sf::Mouse::getPosition(Window::window()) };
					_isDragged = true;
				}
			}
			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					_isDragged = false;
				}
			}
		}

		if (AppData::context.getPlatformControl().first == PlatformControl::Keyboard) {
			if (event.type == sf::Event::KeyPressed) {
				if (event.key == AppData::context.getSwitchKey1().first) {
					_switchingLeft = true;
				}
				if (event.key == AppData::context.getSwitchKey2().first) {
					_switchingRight = true;
				}
			}
			if (event.type == sf::Event::KeyReleased) {
				if (event.key == AppData::context.getSwitchKey1().first) {
					_switchingLeft = false;
				}
				if (event.key == AppData::context.getSwitchKey2().first) {
					_switchingRight = false;
				}
			}
		}
	}
}

void Track::update() {
	if (!isPaused()) {
		if (_isDragged) {
			auto mouse = sf::Vector2f{ sf::Mouse::getPosition(Window::window()) };

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

		MenuItem::update();

		_platforms.update();
	}
}

void Track::init() {
	MenuItem::init();

	Platform::width = 360_deg / static_cast<float>(AppData::context.getPlatformCount().first);
	_platforms.init();

	_switchingLeft = _switchingRight = false;
	_isDragged = false;
}

void Track::resume() {
	_mouse = sf::Vector2f{ sf::Mouse::getPosition(Window::window()) };

	MenuItem::resume();
}
