#pragma once

#include <cmath>
#include <SFML/Graphics.hpp>
#include "Math/Angle.hpp"


/**
 * @brief	Functions for performing mathematic calculations
*/
namespace math {
	/**
	 * @brief	Squares a number
	 * @tparam T	The type of the number
	 * @param num	The number
	 * @return	The result
	*/
	template <typename T>
	T square(T num) {
		return num * num;
	}
	/**
	 * @brief	Squares a number
	 * @param num	The number
	 * @return	The result
	*/
	inline float squaref(float num) {
		return num * num;
	}

	/**
	 * @brief	Calculates the difference between point A and B
	 * @param a	Point A
	 * @param b	Point B
	 * @return	The calculated distance
	*/
	float calcDistance(const sf::Vector2f& a, const sf::Vector2f& b);

	/**
	 * @brief	Calculates the angle of a vector from the origin {0,0}
	 * @param position	The coordinates of the vector
	 * @return	The angle of the vector
	*/
	float calcAngle(const sf::Vector2f& position);

	/**
	 * @brief	Checks whether a value is between two other values
	 * @param val	The value in question
	 * @param smaller	The smaller value
	 * @param bigger	The bigger value
	 * @return	True if the value is in between
	*/
	bool isBetween(float val, float smaller, float bigger);

	/**
	 * @brief	Calculates the points of an arc
	 * @param angle	The middle of the arc in radians
	 * @param spread	The width of the arc
	 * @param radius	The radius of the arc from the origin {0,0}
	 * @param maxpts	The maximum number of points constructing the arc
	 * @return	The points that construct the arc
	*/
	std::vector<sf::Vector2f> getArcPoints(float angle, float spread, float radius, int maxpts);
}
