#include "Track.hpp"

#include "AppData.hpp"
#include "Window.hpp"
#include "Math.hpp"


void Track::draw(sf::RenderTarget& target, const sf::RenderStates& states) const { /*Removed visuals*/ }


Track::Track() {
	addTransition(&_transition);
}


bool Track::isOnPlatform(const sf::Vector2f& point) const {
	return _platforms.isInside(point);
}


void Track::handleEvent(const sf::Event& event) { /*JPorta ruined me*/ }

void Track::update() {
	if (!isPaused()) {
		if (_isDragged) {
			auto mouse = sf::Vector2f{  };

			_platforms.rotate(_preCalc.getPolarVector(mouse).angle - _preCalc.getPolarVector(_mouse).angle);
			_mouse = mouse;
		}

		if (_switchingLeft != _switchingRight) {
			if (_switchingLeft) {
				_transition.start({ -1 * Platform::width, 0.f }, 200);
			}
			if (_switchingRight) {
				_transition.start({ Platform::width, 0.f }, 200);
			}
		}

		MenuItem::update();

		_platforms.update();
	}
}

void Track::init() {
	MenuItem::init();

	Platform::width = 360_deg / 3.f;
	_platforms.init();

	_switchingLeft = _switchingRight = false;
	_isDragged = false;
}

void Track::resume() {
	_mouse = sf::Vector2f{  };

	MenuItem::resume();
}
