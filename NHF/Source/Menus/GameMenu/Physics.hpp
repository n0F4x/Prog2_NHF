#pragma once

#include "Platform.hpp"

class PlatformContainer;


int operator"" _ms(unsigned long long time);	// milliseconds
int operator"" _s(unsigned long long time);		// seconds


namespace Direction {
	static const int POSITIVE = 1;
	static const int NEGATIVE = -1;
};


class Physics {
private:

	// ----------------------Rotation----------------------		SPEED-CURVE: EASE-IN-OUT
private:
	const float _rotationDurationLength = Platform::width;
	int _rotationDurationTime = 100_ms;
	float _rotationAcceleration = _rotationDurationLength / (_rotationDurationTime / 2 * _rotationDurationTime / 2);	// max acceleration during rotation

	bool _isRotating = false;
	int _direction = 0;
	sf::Clock _rotationClock;
	int _rotationTime = 0;
	float _rotationLength = 0;

	void rotate(PlatformContainer& _platforms);
public:
	void rotate(int direction);


	// ----------------------Update----------------------
public:
	void update(PlatformContainer& _platforms);
};

