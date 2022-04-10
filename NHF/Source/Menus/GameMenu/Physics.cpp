#include "Physics.hpp"

#include "PlatformContainer.hpp"


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

void Physics::update(PlatformContainer& _platforms) {
	if (_isRotating) {
		int time = 0;
		if ((time = _rotationClock.getElapsedTime().asMilliseconds()) < _rotationDurationTime) {
			float rotation = 0;
			if (time < _rotationDurationTime / 2) {
				rotation = _rotationAcceleration / 2 * time * time - _rotationAcceleration / 2 * _rotationTime * _rotationTime;
			}
			else {
				rotation = _rotationAcceleration / 2 * (_rotationDurationTime - _rotationTime) * (_rotationDurationTime - _rotationTime) - _rotationAcceleration / 2 * (_rotationDurationTime - time) * (_rotationDurationTime - time);
			}
			_rotationTime = time;
			_rotationLength += rotation;
			_platforms.rotate(rotation * _direction);
		}
		else {
			_platforms.rotate((_rotationDurationLength - _rotationLength) * _direction);
			_rotationTime = 0;
			_rotationLength = 0;
			_isRotating = false;
		}
	}
}