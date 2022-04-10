#pragma once

#include "Platform.hpp"

class PlatformContainer;


enum class Direction {
	POSITIVE,
	NEGATIVE
};


class Physics {
private:

// ----------------------Rotation----------------------
private:
	const float _rotationDurationLength = Platform::width;
	const int _rotationDurationTime = 100;	// in milliseconds
	const float _rotationAcceleration = 2 * _rotationDurationLength / (_rotationDurationTime * _rotationDurationTime);

	bool _isRotating = false;
	int _direction = 0;
	sf::Clock _rotationClock;
	float _rotationLength;
public:
	void rotate(Direction direction);

public:
	void update(PlatformContainer& _platforms);
};

