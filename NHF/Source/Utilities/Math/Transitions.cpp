#include "Transitions.hpp"

#include "Transitionable.hpp"
#include <cmath>


template <typename T>
static float square(T num) {
	return static_cast<float>(num * num);
}


namespace Transitions {
	void EaseInOut::update() {
		if (_isActive) {
			int currentTime;
			if ((currentTime = _clock.getElapsedTime().asMilliseconds()) >= _time) {
				_object->transition(_distance - _currentDistance);
				init();
			}
			else {
				sf::Vector2f currentDistance = { 0.f, 0.f };
				if (currentTime < _time / 2) {
					currentDistance = {
						_accX / 2.f * square(currentTime) - _accX / 2.f * square(_currentTime),
						_accY / 2.f * square(currentTime) - _accY / 2.f * square(_currentTime)
					};
				}
				else {
					currentDistance = {
						_accX / 2.f * square(_time - _currentTime) - _accX / 2.f * square(_time - currentTime),
						_accY / 2.f * square(_time - _currentTime) - _accY / 2.f * square(_time - currentTime)
					};
				}

				_currentTime = currentTime;
				_currentDistance += currentDistance;
				if (fabs(_currentDistance.x) > fabs(_distance.x) || fabs(_currentDistance.y) > fabs(_distance.y)) {
					_object->transition(_distance - _currentDistance);
					init();
				}
				_object->transition(currentDistance);
			}
		}
	}

	void Ease::update() {
		if (_isActive) {
			int currentTime;
			if ((currentTime = _clock.getElapsedTime().asMilliseconds()) >= _time) {
				_object->transition(_distance - _currentDistance);
				init();
			}
			else {
				float progress = _bezier.GetEasingProgress(static_cast<float>(currentTime) / static_cast<float>(_time)) - _lastProgress;
				sf::Vector2f currentDistance = _distance * progress;

				_currentTime = currentTime;
				_currentDistance += currentDistance;
				_lastProgress += progress;
				_object->transition(currentDistance);
			}
		}
	}
}
