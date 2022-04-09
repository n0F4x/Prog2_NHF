#pragma once

#include <SFML/Graphics.hpp>
#include "../../Utilities/Math/Angle.hpp"


class Platform {
private:
	static float _maxRadius;
	static float _scalingRatio;
	static const float _width;

	float _innerRadius = 2.f;
	float _outerRadius = 3.f;
	float _rotation = 0_deg;

public:
	static void setOrigin(sf::Vector2f origin);
	static void setScale(int speed);

	Platform(float rotation = 75_deg);

	float getInnerRadius() const { return _innerRadius; }
	float getOuterRadius() const { return _outerRadius; }
	float getRotation() const { return _rotation; }
	float getWidth() const { return _width; }

	void rotate(float angle);

	void update();
	bool isDead() const;
};
