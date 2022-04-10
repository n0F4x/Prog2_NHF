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
	const float _rotationAcceleration = _rotationDurationLength / (_rotationDurationTime / 2 * _rotationDurationTime / 2);

	bool _isRotating = false;
	int _direction = 0;
	sf::Clock _rotationClock;
	int _rotationTime = 0;
	float _rotationLength = 0;
public:
	void rotate(Direction direction);

public:
	void update(PlatformContainer& _platforms);
};

