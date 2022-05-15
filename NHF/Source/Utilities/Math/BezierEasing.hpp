#pragma once		/// Credits for https://github.com/Trodek/Bezier-Easing ///

#include <vector>
#include <SFML/Graphics.hpp>


/**
 * @brief	Class for calculating cubic bezier easing
*/
class BezierEasing {
public:
	/**
	 * @brief	Creates a cubic Bezier easing for any p1 and p2 with components between 0 and 1
	 * @param p1	One point of the easing
	 * @param p2	Another point of the easing
	*/
	BezierEasing(const sf::Vector2f& p1, const sf::Vector2f& p2);

	/**
	 * @brief	Calculates progress for desired time if valid curve. -1 if invalid
	 * @param t	The desired time
	 * @return	The progress of the easing from 0 to t
	*/
	float GetEasingProgress(float t);

private:
	// Calculate support vectors
	float VecACoord(float p1_coord, float p2_coord) const;
	float VecBCoord(float p1_coord, float p2_coord) const;
	float VecCCoord(float p1_coord) const;

	//Calculate the Bezier point
	float CalcBezier(float time, float p1_coord, float p2_coord) const;

	//Calculate Bezier Slope
	float GetSlope(float time, float p1_coord, float p2_coord) const;

	float BinarySubdivide(float time, float interval_start, float next_interval_step, float p1_coord, float p2_coord) const;

	float NewtonRaphsonIterate(float time, float guessed_t, float p1_coord, float p2_coord) const;

	float GetXForTime(float time);

	//Check if the points are in the valid range
	bool CheckPoints() const;


// Variables
	sf::Vector2f _p1{ 0.f, 0.f };
	sf::Vector2f _p2{ 0.f, 0.f };

	std::vector<float> _sample_values;

	float _last_value = 0.f;

	bool _valid = true;
};
