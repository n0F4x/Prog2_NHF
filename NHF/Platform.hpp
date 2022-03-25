#pragma once

#include <SFML/Graphics.hpp>

#include "Engine.hpp"


class Platform {
private:
	Engine& _Engine;

	static sf::Vector2f _origin;
	static float _maxRadius;
	static float _scalingRatio;

	float _outerRadius = 3.1f;
	float _innerRadius = 1.9f;
	Angle _rotation = 0_deg;
	const Angle _width = 30_deg;

	sf::Vector2f _center;
	float _centerRadius = sqrt(0.7f);

public:
	static void setOrigin(sf::Vector2f origin);
	static void setScale(int speed);

	Platform(Engine& _Engine, Angle rotation = 255_deg);

	bool isInside(sf::Vector2f point) const;

	void rotate(Angle angle);

	void update();
	bool isDead() const;
};
