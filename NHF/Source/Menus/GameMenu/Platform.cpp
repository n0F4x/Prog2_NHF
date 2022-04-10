#include "Platform.hpp"

#include <cmath>


inline float angle(sf::Vector2f v) {
    return std::atan2(v.y, v.x);
}

inline std::vector<sf::Vector2f> getCirclePoints(float angle, float radius) {
    std::vector<sf::Vector2f> ret;
    const int maxpts = 20;
    const float spread = Platform::width;
    for (int i = 0; i < maxpts; ++i) {
        const float a = (angle - spread / 2.f) + (i * spread) / (maxpts - 1);
        ret.push_back(radius * sf::Vector2f(std::cos(a), std::sin(a)));
    }
    return ret;
}


const float Platform::width = 360_deg / 4;

float Platform::_maxRadius = 0.f;
sf::Vector2f Platform::_origin = sf::Vector2f{ 0.f, 0.f };
void Platform::setOrigin(const sf::Vector2f& origin) {
	_maxRadius = sqrt(origin.x * origin.x + origin.y * origin.y);
	_origin = origin;
}

float Platform::_scalingRatio = 1.0;
void Platform::setScale(int speed) {
	_scalingRatio = powf(3.f / 2.f, 1.0f / speed);
}


void Platform::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::VertexArray arr(sf::TriangleFan);
    arr.append(sf::Vertex(_origin));
    for (sf::Vector2f v : getCirclePoints(_rotation, _outerRadius))
        arr.append(sf::Vertex(_origin + v));

    arr.append(sf::Vertex(_origin));

    target.draw(arr);
    sf::CircleShape innerCircle{_innerRadius};
    innerCircle.setPosition(_origin - sf::Vector2f{_innerRadius, _innerRadius});
    innerCircle.setFillColor(sf::Color::Black);
    target.draw(innerCircle);
}



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
