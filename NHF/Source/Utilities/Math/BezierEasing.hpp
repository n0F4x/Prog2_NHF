#pragma once		/// Credits for https://github.com/Trodek/Bezier-Easing ///

#include <vector>
#include <SFML/Graphics.hpp>


class BezierEasing {
public:
	//Create a cubic Bezier easing for any p1 and p2 with components between 0 and 1
	BezierEasing(const sf::Vector2f& p1, const sf::Vector2f& p2);

	~BezierEasing();

	//Return progress for desired time if valid curve. -1 if invalid.
	float GetEasingProgress(float t);

private:

	// Calculate support vectors
	float VecACoord(float p1_coord, float p2_coord);
	float VecBCoord(float p1_coord, float p2_coord);
	float VecCCoord(float p1_coord);

	//Calculate the Bezier point
	float CalcBezier(float time, float p1_coord, float p2_coord);

	//Calculate Bezier Slope
	float GetSlope(float time, float p1_coord, float p2_coord);

	float BinarySubdivide(float time, float interval_start, float next_interval_step, float p1_coord, float p2_coord);

	float NewtonRaphsonIterate(float time, float guessed_t, float p1_coord, float p2_coord);

	float GetXForTime(float time);

	//Check if the points are in the valid range
	bool CheckPoints(const sf::Vector2f& p1, const sf::Vector2f& p2);

public:

private:
	sf::Vector2f _p1{ 0.f, 0.f };
	sf::Vector2f _p2{ 0.f, 0.f };

	std::vector<float> _sample_values;

	float _last_value = 0.0f;

	bool _valid = true;
};
