#pragma once

#include "SFMLDrawable.hpp"
#include "SFMLVector2.hpp"
#include "PreCalculator.hpp"
#include "Angle.hpp"


class Platform : public sf::Drawable {
public:
	static float width;

private:
	static const float _initInnerRadius;
	static const float _initOuterRadius;

	static sf::Vector2f _origin;
	static float _maxRadius;
	static float _scalingRatio;

	// Non-static
	const PreCalculator& _preCalc;

	float _innerRadius = _initInnerRadius;
	float _outerRadius = _initOuterRadius;
	float _rotation = 0_deg;

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

public:
	static void setOrigin(const sf::Vector2f& origin);
	static void setScale(int speed);

	Platform(const PreCalculator& preCalc, float rotation = 90_deg - width / 2);

	float getInnerRadius() const { return _innerRadius; }
	float getOuterRadius() const { return _outerRadius; }
	float getRotation() const { return _rotation; }
	float getWidth() const { return width; }

	bool isInside(const sf::Vector2f& point) const;

	void rotate(float angle);

	void update();
	bool isDead() const;
};
