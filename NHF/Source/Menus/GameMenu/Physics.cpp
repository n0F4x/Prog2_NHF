#include "Physics.hpp"

#include "PlatformContainer.hpp"


static int square(int num) {
	return num * num;
}


void Physics::rotate(Direction direction) {
	if (!_isRotating) {
		switch (direction) {
		case Direction::POSITIVE:
			_direction = 1;
			break;
		case Direction::NEGATIVE:
			_direction = -1;
			break;
		default:
			break;
		}
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
		_rotationLength += rotation;

		if (_rotationLength >= _rotationDurationLength || _rotationTime >= _rotationDurationTime) {
			_platforms.rotate((_rotationLength - _rotationDurationLength) * _direction);
			_rotationTime = 0;
			_rotationLength = 0;
			_isRotating = false;
		}
		else {
			_platforms.rotate(rotation * _direction);
		}
	}
}

void Physics::update(PlatformContainer& _platforms) {
	rotate(_platforms);
}