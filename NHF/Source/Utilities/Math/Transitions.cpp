#include "Transitions.hpp"

#include "Transitionable.hpp"

template <typename T>
static T square(T num) {
	return num * num;
}

namespace Transitions {
	void EaseInOut::update() {
		if (_isActive) {
			int currentTime = _clock.getElapsedTime().asMilliseconds();
			sf::Vector2f currentDistance = { 0.f, 0.f };

			if (currentTime < _time / 2) {
				currentDistance = {
					_accX / 2 * square(currentTime) - _accX / 2 * square(_currentTime),
					_accY / 2 * square(currentTime) - _accY / 2 * square(_currentTime)
				};
			}
			else {
				currentDistance = {
					_accX / 2 * square(_time - _currentTime) - _accX / 2 * square(_time - currentTime),
					_accY / 2 * square(_time - _currentTime) - _accY / 2 * square(_time - currentTime)
				};
			}

			_currentTime = currentTime;

			if (_currentTime >= _time) {
				_object->transition(_distance - _currentDistance);
				init();
			}
			else {
				_currentDistance += currentDistance;
				_object->transition(currentDistance);
			}
		}
	}
}
