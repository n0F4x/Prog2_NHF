#pragma once

#include "Platform.hpp"

class PlatformContainer;


enum class Direction {
	POSITIVE,
	NEGATIVE
};


class Physics {
private:

// ----------------------Rotation----------------------		SPEED-CURVE: EASE-IN-OUT
private:
	const float _rotationDurationLength = Platform::width;
	const int _rotationDurationTime = 100;	// in milliseconds
	const float _rotationAcceleration = _rotationDurationLength / (_rotationDurationTime / 2 * _rotationDurationTime / 2);	// max acceleration during rotation

	bool _isRotating = false;
	int _direction = 0;
	sf::Clock _rotationClock;
	int _rotationTime = 0;
	float _rotationLength = 0;

	void rotate(PlatformContainer& _platforms);
public:
	void rotate(Direction direction);


// ----------------------Update----------------------
public:
	void update(PlatformContainer& _platforms);
};

