#include "Platform.hpp"

#include "../../GUI/Theme.hpp"
#include <cmath>


std::vector<sf::Vector2f> getArcPoints(float angle, float radius) {
	std::vector<sf::Vector2f> pts;
	const int maxpts = 20;
	const float spread = Platform::width;
	for (int i = 0; i < maxpts; ++i) {
		const float a = (angle - spread / 2.f) + (i * spread) / (maxpts - 1);
		pts.emplace_back(radius * sf::Vector2f{ cos(a), sin(a) });
	}
	return pts;
}


const float Platform::width = 360_deg / 8;
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
	_scalingRatio = powf(_initOuterRadius / _initInnerRadius, 1.f / speed);
}


void Platform::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	// Magic circle segment
	sf::VertexArray arr{ sf::TriangleFan };
	sf::Vertex origin{ _origin };
	origin.color = _preCalc.getColor(_origin);

	arr.append(origin);
	for (const sf::Vector2f& v : getArcPoints(_rotation + width / 2.f, _outerRadius)) {
		sf::Vertex point{ _origin + v };
		point.color = _preCalc.getColor(point.position);
		arr.append(point);
	}
	arr.append(origin);

	target.draw(arr);

	// Hide inner circle
	sf::CircleShape innerCircle{ _innerRadius, 50 };
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
