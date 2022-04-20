#include "BezierEasing.hpp"

#include <math.h>

#define NEWTON_ITERATIONS 4
#define NEWTON_MIN_SLOPE 0.001f
#define SUBDIVISION_PRECISION 0.0000001f
#define SUBDIVISION_MAX_ITERATIONS 10

#define SAMPLES_SIZE 11
#define SAMPLES_STEP (1.0f / (SAMPLES_SIZE - 1))


BezierEasing::BezierEasing(const sf::Vector2f& p1, const sf::Vector2f& p2) : _p1{ p1 }, _p2{ p2 } {
	_valid = CheckPoints(_p1, _p2);

	//Precompute the Samples for this Bezier curve if no linear
	if (_valid && _p1.x != _p1.y && _p2.x != _p2.y) {
		for (int i = 0; i < SAMPLES_SIZE; ++i) {
			_sample_values.push_back(CalcBezier(i * SAMPLES_STEP, _p1.x, _p2.x));
		}
	}
}

BezierEasing::~BezierEasing() {}

float BezierEasing::GetEasingProgress(float t) {
	if (_valid) {
		if (_p1.x == _p1.y && _p2.x == _p2.y) //linear progression
		{
			_last_value = (t <= 1) ? t : 1.0f;
		}
		else if (t == 0) {
			_last_value = 0.0f;
		}
		else if (t >= 1) {
			_last_value = 1.0f;
		}
		else {
			float curr_value = CalcBezier(GetXForTime(t), _p1.y, _p2.y);

			curr_value = (curr_value <= 1) ? curr_value : _last_value;

			_last_value = (curr_value > _last_value) ? curr_value : _last_value;
		}

		return _last_value;
	}
	else
		return -1;
}

float BezierEasing::VecACoord(float p1_coord, float p2_coord) {
	return 1.0f - 3.0f * p2_coord + 3.0 * p1_coord;
}

float BezierEasing::VecBCoord(float p1_coord, float p2_coord) {
	return 3.0f * p2_coord - 6.0f * p1_coord;
}

float BezierEasing::VecCCoord(float p1_coord) {
	return 3.0f * p1_coord;
}

float BezierEasing::CalcBezier(float time, float p1_coord, float p2_coord) {
	return ((VecACoord(p1_coord, p2_coord) * time + VecBCoord(p1_coord, p2_coord)) * time + VecCCoord(p1_coord)) * time;
}

float BezierEasing::GetSlope(float time, float p1_coord, float p2_coord) {
	return 3.0f * VecACoord(p1_coord, p2_coord) * time * time + 2.0f * VecBCoord(p1_coord, p2_coord) * time + VecCCoord(p1_coord);
}

float BezierEasing::BinarySubdivide(float time, float interval_start, float next_interval_step, float p1_coord, float p2_coord) {
	float current_x, current_t;
	int i = 0;

	do {
		current_t = interval_start + (next_interval_step - interval_start) / 2.0f;
		current_x = CalcBezier(current_t, p1_coord, p2_coord) - time;
		if (current_x > 0.0f) {
			next_interval_step = current_t;
		}
		else {
			interval_start = current_t;
		}
	} while (abs(current_x) > SUBDIVISION_PRECISION && ++i < SUBDIVISION_MAX_ITERATIONS);

	return current_t;
}

float BezierEasing::NewtonRaphsonIterate(float time, float guessed_t, float p1_coord, float p2_coord) {
	for (int i = 0; i < NEWTON_ITERATIONS; ++i) {
		float curr_slope = GetSlope(guessed_t, p1_coord, p2_coord);
		if (curr_slope == 0.0f) {
			return guessed_t;
		}
		float curr_x = CalcBezier(guessed_t, p1_coord, p2_coord) - time;
		guessed_t -= curr_x / curr_slope;
	}

	return guessed_t;
}

float BezierEasing::GetXForTime(float time) {
	float interval_start = 0.0f;
	int curr_sample = 1;

	for (; curr_sample < SAMPLES_SIZE && _sample_values[curr_sample] <= time; ++curr_sample) {
		interval_start += SAMPLES_STEP;
	}
	--curr_sample;

	//Interpolate to get a first guessed X
	float dist = (time - _sample_values[curr_sample]) / (_sample_values[curr_sample + 1] - _sample_values[curr_sample]);
	float guess_for_x = interval_start + dist * SAMPLES_STEP;
	// ------

	float initial_slope = GetSlope(guess_for_x, _p1.x, _p2.x);

	if (initial_slope >= NEWTON_MIN_SLOPE) {
		return NewtonRaphsonIterate(time, guess_for_x, _p1.x, _p2.x);
	}
	else if (initial_slope == 0.0f) {
		return guess_for_x;
	}
	else {
		return BinarySubdivide(time, interval_start, interval_start + SAMPLES_STEP, _p1.x, _p2.x);
	}
}

bool BezierEasing::CheckPoints(const sf::Vector2f& p1, const sf::Vector2f& p2) {
	return ((_p1.x >= 0 && _p1.x <= 1)
		&& (_p1.y >= 0 && _p1.y <= 1)
		&& (_p2.x >= 0 && _p2.x <= 1)
		&& (_p2.y >= 0 && _p2.y <= 1));
}
