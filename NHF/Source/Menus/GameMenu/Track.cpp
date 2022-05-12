#include "Track.hpp"

#include "../../Utilities/Math.hpp"


void Track::switchLanes() {
	if (_holdSwitch) {
		if (_switchingLeft != _switchingRight) {
			if (_switchingLeft) {
				_transition.start({ -1 * _platforms.getPlatformWidth(), 0.f }, 200 * 3 / _laneCount);
			}
			if (_switchingRight) {
				_transition.start({ _platforms.getPlatformWidth(), 0.f }, 200 * 3 / _laneCount);
			}
		}
	}
	else {
		if (_switchingState != 0 && !_transition.isActive()) {
			if (_switchingState > 0) {
				_transition.start({ _platforms.getPlatformWidth(), 0.f }, 200 * 3 / _laneCount);
				_switchingState--;
			}
			else {
				_transition.start({ -1 * _platforms.getPlatformWidth(), 0.f }, 200 * 3 / _laneCount);
				_switchingState++;
			}
		}
	}
}


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


bool Track::isOnPlatforms(const sf::Vector2f& point) const {
	return _platforms.isInside(_preCalc.getPolarVector(point));
}

bool Track::AI_jump(const sf::Vector2f& playerFeet) {
	return _platforms.AI_help(_preCalc.getPolarVector(playerFeet), _switchingState);
}


void Track::handleEvent(const sf::Event& event) {
	if (!isPaused()) {
		if (_platformControl == PlatformControl::Mouse) {
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				_mouse = sf::Vector2f{ sf::Mouse::getPosition(Window::window()) };
				_isDragged = true;
			}
			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
				_isDragged = false;
			}
		}
		if (_platformControl == PlatformControl::Keyboard) {
			if (_holdSwitch) {
				if (event.type == sf::Event::KeyPressed) {
					if (event.key == _switchKey1) {
						_switchingLeft = true;
					}
					if (event.key == _switchKey2) {
						_switchingRight = true;
					}
				}
				if (event.type == sf::Event::KeyReleased) {
					if (event.key == _switchKey1) {
						_switchingLeft = false;
					}
					if (event.key == _switchKey2) {
						_switchingRight = false;
					}
				}
			}
			else if (event.type == sf::Event::KeyPressed) {
				if (event.key == _switchKey1) {
					_switchingState--;
				}
				if (event.key == _switchKey2) {
					_switchingState++;
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

		switchLanes();

		MenuItem::update();

		_platforms.update();
	}
}

void Track::init() {
	MenuItem::init();

	_laneCount = AppData::findContext("laneCount")->get<unsigned>();
	_platformControl.update();
	_switchKey1.update();
	_switchKey2.update();
	_holdSwitch.update();

	_platforms.init(_laneCount, _platformSpeed);

	_isDragged = false;
	_switchingState = 0;
	_switchingLeft = false;
	_switchingRight = false;
}

void Track::resume() {
	_mouse = sf::Vector2f{ sf::Mouse::getPosition(Window::window()) };

	_switchingLeft = false;
	_switchingRight = false;

	MenuItem::resume();
}
