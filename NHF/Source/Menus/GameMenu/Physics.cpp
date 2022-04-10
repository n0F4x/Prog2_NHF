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
//#include <iostream>
void Physics::update(PlatformContainer& _platforms) {
	if (_isRotating) {
		int time = 0;
		if ((time = _rotationClock.getElapsedTime().asMilliseconds()) <= _rotationDurationTime) {
			float rotation = 0;
			if (time < _rotationDurationTime / 2) {
				rotation = _rotationAcceleration * time * time - _rotationLength;
			}
			else {
				rotation = _rotationAcceleration * (_rotationDurationTime - time) * (_rotationDurationTime - time);
			}
			_rotationLength += rotation;
			//std::cout << rotation << std::endl;
			_platforms.rotate(rotation * _direction);
		}
		else {
			//std::cout << _rotationDurationLength - _rotationLength << std::endl;
			_platforms.rotate((_rotationDurationLength - _rotationLength) * _direction);
			_rotationLength = 0;
			_isRotating = false;
		}
	}
}