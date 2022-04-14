#include "Physics.hpp"

#include "PlatformContainer.hpp"


int operator""_ms(unsigned long long time) { return static_cast<int>(time); }
int operator"" _s(unsigned long long time) { return static_cast<int>(time * 1000); }

static int square(int num) {
	return num * num;
}


void Physics::rotate(int direction) {
	if (!_isRotating) {
		_direction = direction;
		_isRotating = true;
		_rotationClock.restart();
	}
}

void Physics::rotate(PlatformContainer& _platforms) {
	if (_isRotating) {
		int time = _rotationClock.getElapsedTime().asMilliseconds();
		float rotation = 0;

		if (time < _rotationDurationTime / 2) {
			rotation = _rotationAcceleration / 2 * square(time) - _rotationAcceleration / 2 * square(_rotationTime);
		}
		else {
			rotation = _rotationAcceleration / 2 * square(_rotationDurationTime - _rotationTime) - _rotationAcceleration / 2 * square(_rotationDurationTime - time);
		}

		_rotationTime = time;

		if (_rotationLength + rotation >= _rotationDurationLength || _rotationTime >= _rotationDurationTime) {
			_platforms.rotate((_rotationDurationLength - _rotationLength) * _direction);
			_rotationTime = 0;
			_rotationLength = 0;
			_isRotating = false;
		}
		else {
			_rotationLength += rotation;
			_platforms.rotate(rotation * _direction);
		}
	}
}

void Physics::update(PlatformContainer& _platforms) {
	rotate(_platforms);
}
