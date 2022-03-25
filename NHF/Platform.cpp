#include "Platform.hpp"


sf::Vector2f Platform::_origin = { 0.f, 0.f };
float Platform::_maxRadius = 0.f;
void Platform::setOrigin(sf::Vector2f origin) {
	_origin = origin;
	_maxRadius = sqrt(origin.x * origin.x + origin.y * origin.y);
}

float Platform::_scalingRatio = 1.0;
void Platform::setScale(int speed) {
	_scalingRatio = pow(1.5f, 1.0f / speed);
}

Platform::Platform(Engine& Engine, Angle rotation) :
	_Engine{ Engine },
	_center{ _origin.x + 2.588190451f, _origin.y } {
	while (rotation >= 360_deg) rotation -= 360_deg;
	while (rotation < 0_deg) rotation += 360_deg;
	_rotation = rotation;

	math::rotate(_center, _origin, _rotation + _width / 2.f);
}

void Platform::rotate(Angle angle) {
	_rotation += angle;
	while (_rotation >= 360_deg) _rotation -= 360_deg;
	while (_rotation < 0_deg) _rotation += 360_deg;

	math::rotate(_center, _origin, angle);
}

void Platform::update() {
	_innerRadius *= _scalingRatio;
	_outerRadius *= _scalingRatio;
	_center = (_center - _origin) * _scalingRatio + _origin;
	_centerRadius *= _scalingRatio;
}

bool Platform::isInside(sf::Vector2f point) const {
	if (math::isInsideCircle(_center, _centerRadius, point))
		if (math::isBetween(_origin, _innerRadius, _outerRadius, point))
			if (math::isBetween(_Engine.getAngle(point), _rotation, _rotation + _width))
				return true;
	return false;
}

bool Platform::isDead() const {
	return _innerRadius >= _maxRadius;
}
