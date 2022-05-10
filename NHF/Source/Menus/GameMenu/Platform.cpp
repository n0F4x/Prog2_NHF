#include "Platform.hpp"

#include "../../GUI/Theme.hpp"
#include "../../Utilities/Math.hpp"


float Platform::width = 360_deg / 8;
const float Platform::_initInnerRadius = 2.f;
const float Platform::_initOuterRadius = 4.f;

float Platform::_maxRadius = 0.f;
sf::Vector2f Platform::_origin = sf::Vector2f{ 0.f, 0.f };
void Platform::setOrigin(const sf::Vector2f& origin) {
	_maxRadius = sqrt(math::squaref(origin.x) + math::squaref(origin.y));
	_origin = origin;
}

float Platform::_scalingRatio = 1.0;
void Platform::setScale(int speed) {
	_scalingRatio = powf(_initOuterRadius / _initInnerRadius, 1.f / static_cast<float>(speed));
}


void Platform::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	// Magic circle segment
	sf::VertexArray arr{ sf::TriangleFan };
	sf::Vertex origin{ _origin };
	origin.color = theme::Purple;

	arr.append(origin);
	for (const sf::Vector2f& v : math::getArcPoints(_rotation + width / 2.f, Platform::width, _outerRadius + 0.3f, 40)) {
		sf::Vertex point{ _origin + v };
		point.color = theme::Purple;
		arr.append(point);
	}
	arr.append(origin);

	target.draw(arr);

	// Hide inner circle
	sf::CircleShape innerCircle{ _innerRadius, 108 };
	innerCircle.setPosition(_origin - sf::Vector2f{ _innerRadius, _innerRadius });
	innerCircle.setFillColor(sf::Color::Black);
	target.draw(innerCircle);
}


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
	PolarVector polarV = _preCalc.getPolarVector(point);
	return
		math::isBetween(polarV.radius, _innerRadius, _outerRadius) &&
		math::isBetween(polarV.angle, _rotation, _rotation + width) || math::isBetween(polarV.angle + 360_deg, _rotation, _rotation + width);
}
