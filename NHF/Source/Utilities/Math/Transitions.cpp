#include "Transitions.hpp"

#include "Transitionable.hpp"


static int square(int num) {
	return num * num;
}


namespace Transitions {
	void EaseInOut::update() {
		if (_isActive) {
			int time = _clock.getElapsedTime().asMilliseconds();
			float rotation = 0;

			if (time < _time / 2) {
				rotation = _acceleration / 2 * square(time) - _acceleration / 2 * square(_currentTime);
			}
			else {
				rotation = _acceleration / 2 * square(_time - _currentTime) - _acceleration / 2 * square(_time - time);
			}

			_currentTime = time;

			if (_currentLength + rotation >= _length || _currentTime >= _time) {
				_object->transition((_length - _currentLength) * _direction);
				_currentTime = 0;
				_currentLength = 0;
				_isActive = false;
			}
			else {
				_currentLength += rotation;
				_object->transition(rotation * _direction);
			}
		}
	}
}