#include "Platform.hpp"

#include "Math.hpp"


float Platform::width = 360_deg / 8;
const float Platform::_initInnerRadius = 2.f;
const float Platform::_initOuterRadius = 4.f;

float Platform::_maxRadius = 0.f;
sf::Vector2f Platform::_origin = sf::Vector2f{ 0.f, 0.f };
void Platform::setOrigin(const sf::Vector2f& origin) {
	_maxRadius = sqrt(origin.x * origin.x + origin.y * origin.y);
	_origin = origin;
}

float Platform::_scalingRatio = 1.0;
void Platform::setScale(int speed) {
	_scalingRatio = powf(_initOuterRadius / _initInnerRadius, 1.f / static_cast<float>(speed));
}


void Platform::draw(sf::RenderTarget&, const sf::RenderStates&) const { /*Removed visuals*/ }


Platform::Platform(const PreCalculator& preCalc, float rotation) : _preCalc{ preCalc } {
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

bool Platform::isInside(const sf::Vector2f& point) const {
	float distance = math::calcDistance(_origin, point);
	if (distance > _innerRadius && distance < _outerRadius) {
		float angle = math::calcAngle(_origin - point);
		if ((angle > _rotation && angle < _rotation + width) || (angle + 360_deg > _rotation && angle + 360_deg < _rotation - width)) {
			return true;
		}
	}
	return false;
}
