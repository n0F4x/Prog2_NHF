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

#include <iostream>
void Physics::rotate(PlatformContainer& _platforms) {
	if (_isRotating) {
		int time = 0;
		if ((time = _rotationClock.getElapsedTime().asMilliseconds()) < _rotationDurationTime) {
			float rotation = 0;
			if (time < _rotationDurationTime / 2) {
				rotation = _rotationAcceleration / 2 * square(time) - _rotationAcceleration / 2 * square(_rotationTime);
			}
			else {
				rotation = _rotationAcceleration / 2 * square(_rotationDurationTime - _rotationTime) - _rotationAcceleration / 2 * square(_rotationDurationTime - time);
			}
			_rotationTime = time;
			_rotationLength += rotation;
			_platforms.rotate(rotation * _direction);
		}
		else {
			std::cout << _rotationDurationLength - _rotationLength << std::endl;
			_platforms.rotate((_rotationDurationLength - _rotationLength) * _direction);
			_rotationTime = 0;
			_rotationLength = 0;
			_isRotating = false;
		}
	}
}

void Physics::update(PlatformContainer& _platforms) {
	rotate(_platforms);
}