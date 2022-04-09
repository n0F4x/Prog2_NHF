#pragma once

#include <SFML/Graphics.hpp>
#include "../../Utilities/Math/Angle.hpp"


class Platform {
public:
	static const float width;

private:
	static float _maxRadius;
	static float _scalingRatio;

	float _innerRadius = 2.f;
	float _outerRadius = 3.f;
	float _rotation = 0_deg;

public:
	static void setOrigin(sf::Vector2f origin);
	static void setScale(int speed);

	Platform(float rotation = 90_deg - width / 2);

	float getInnerRadius() const { return _innerRadius; }
	float getOuterRadius() const { return _outerRadius; }
	float getRotation() const { return _rotation; }
	float getWidth() const { return width; }

	void rotate(float angle);

	void update();
	bool isDead() const;
};
