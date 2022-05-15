#pragma once

#include <SFML/Graphics.hpp>
#include "PreCalculator.hpp"
#include "../../Utilities/Math/Angle.hpp"


/**
 * @brief	Class that displays and manages a platform
*/
class Platform : public sf::Drawable {
private:
	static const float _initInnerRadius;
	static const float _initOuterRadius;

	static sf::Vector2f _origin;
	static float _maxRadius;

	// Non-static
	const PreCalculator& _preCalc;

	float _scalingRatio;
	/**
	 * @brief	Setter for _scalingRatio
	 * @param speed	The amount of times a platform needs to be updated to move by a range of 1 platform
	*/
	void setScale(unsigned speed);

	float _innerRadius = _initInnerRadius;
	float _outerRadius = _initOuterRadius;
	float _rotation = 0_deg;
	const float _width;

	/**
	 * @brief	Draws the platform to the render target
	 * @param target	The render target
	 * @param target	The render states
	*/
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	/**
	 * @brief	Setter for _origin
	 * @param origin	The new origin 
	*/
	static void setOrigin(const sf::Vector2f& origin);

	/**
	 * @brief	Constructs a new Platform
	 * @param preCalc	Reference to a pre-calculator
	 * @param rotation	Initial rotation of the platform (in radians)
	 * @param width		Width of the platform (in radians)
	 * @param speed		The amount of times a platform needs to be updated to move by a range of 1 platform
	*/
	Platform(const PreCalculator& preCalc, float rotation, float width, unsigned speed);

	/**
	 * @brief	Getter for inner radius
	 * @return	The inner radius of the platform
	*/
	float getInnerRadius() const { return _innerRadius; }
	/**
	 * @brief	Getter for outer radius
	 * @return	The outer radius of the platform
	*/
	float getOuterRadius() const { return _outerRadius; }
	/**
	 * @brief	Getter for rotation
	 * @return	The rotation of the platform in radians
	*/
	float getRotation() const { return _rotation; }
	/**
	 * @brief	Getter for width
	 * @return	The width of the platform in radians
	*/
	float getWidth() const { return _width; }

	/**
	 * @brief	Check whether a point is on the platform
	 * @param point	The point in question
	 * @return	True if the point is on the platform
	*/
	bool isInside(const PolarVector& point) const;

	/**
	 * @brief	Rotates the platform by the amount given as param
	 * @param angle	The amount that will be added to the platforms rotation (in radians)
	*/
	void rotate(float angle);

	/**
	 * @brief	Updates the platform
	*/
	void update();
	/**
	 * @brief	Checks whether the platform is still inside the area of the window
	 * @return	True if the platform is outside
	*/
	bool isDead() const;
};
