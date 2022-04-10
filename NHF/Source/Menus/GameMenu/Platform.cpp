#include "Platform.hpp"


float Platform::_maxRadius = 0.f;
void Platform::setOrigin(sf::Vector2f origin) {
	_maxRadius = sqrt(origin.x * origin.x + origin.y * origin.y);
}

float Platform::_scalingRatio = 1.0;
void Platform::setScale(int speed) {
	_scalingRatio = powf(3.f / 2.f, 1.0f / speed);
}

const float Platform::width = 360_deg / 4;


Platform::Platform(float rotation) {
	rotate(rotation);
}


void Platform::rotate(float angle) {
	_rotation += angle;
	while (_rotation >= 360_deg) _rotation -= 360_deg;
	while (_rotation < 0_deg) _rotation += 360_deg;
}

void Platform::update() {
	_innerRadius *= _scalingRatio;
	_outerRadius *= _scalingRatio;
}

bool Platform::isDead() const {
	return _innerRadius > _maxRadius;
}
