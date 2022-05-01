#include "BezierEasing.hpp"

#include <math.h>

constexpr int NEWTON_ITERATIONS = 4;
constexpr float NEWTON_MIN_SLOPE = 0.001f;
constexpr float SUBDIVISION_PRECISION = 0.0000001f;
constexpr int SUBDIVISION_MAX_ITERATIONS = 10;

constexpr int SAMPLES_SIZE = 11;
constexpr float SAMPLES_STEP = 1.f / (SAMPLES_SIZE - 1);


BezierEasing::BezierEasing(const sf::Vector2f& p1, const sf::Vector2f& p2) : _p1{ p1 }, _p2{ p2 } {
	_valid = CheckPoints();

	//Precompute the Samples for this Bezier curve if no linear
	if (_valid && _p1.x != _p1.y && _p2.x != _p2.y) {
		for (int i = 0; i < SAMPLES_SIZE; ++i) {
			_sample_values.push_back(CalcBezier(static_cast<float>(i) * SAMPLES_STEP, _p1.x, _p2.x));
		}
	}
}

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

float BezierEasing::VecACoord(float p1_coord, float p2_coord) const {
	return 1.f - 3.f * p2_coord + 3.f * p1_coord;
}

float BezierEasing::VecBCoord(float p1_coord, float p2_coord) const {
	return 3.f * p2_coord - 6.f * p1_coord;
}

float BezierEasing::VecCCoord(float p1_coord) const {
	return 3.f * p1_coord;
}

float BezierEasing::CalcBezier(float time, float p1_coord, float p2_coord) const {
	return ((VecACoord(p1_coord, p2_coord) * time + VecBCoord(p1_coord, p2_coord)) * time + VecCCoord(p1_coord)) * time;
}

float BezierEasing::GetSlope(float time, float p1_coord, float p2_coord) const {
	return 3.0f * VecACoord(p1_coord, p2_coord) * time * time + 2.0f * VecBCoord(p1_coord, p2_coord) * time + VecCCoord(p1_coord);
}

float BezierEasing::BinarySubdivide(float time, float interval_start, float next_interval_step, float p1_coord, float p2_coord) const {
	float current_x;
	float current_t;
	int i = 0;

	do {
		current_t = std::lerp(interval_start, next_interval_step, 0.5f);
		current_x = CalcBezier(current_t, p1_coord, p2_coord) - time;
		if (current_x > 0.f) {
			next_interval_step = current_t;
		}
		else {
			interval_start = current_t;
		}
		i++;
	} while (fabs(current_x) > SUBDIVISION_PRECISION && i < SUBDIVISION_MAX_ITERATIONS);

	return current_t;
}

float BezierEasing::NewtonRaphsonIterate(float time, float guessed_t, float p1_coord, float p2_coord) const {
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
	float interval_start = 0.f;
	int curr_sample = 1;

	for (; curr_sample < SAMPLES_SIZE && _sample_values[curr_sample] <= time; ++curr_sample) {
		interval_start += SAMPLES_STEP;
	}
	--curr_sample;

	//Interpolate to get a first guessed X
	float dist = (time - _sample_values[curr_sample]) / (_sample_values[static_cast<size_t>(curr_sample) + 1u] - _sample_values[curr_sample]);
	float guess_for_x = interval_start + dist * SAMPLES_STEP;
	// ------

	float initial_slope = GetSlope(guess_for_x, _p1.x, _p2.x);

	if (initial_slope >= NEWTON_MIN_SLOPE) {
		return NewtonRaphsonIterate(time, guess_for_x, _p1.x, _p2.x);
	}
	else if (initial_slope == 0.f) {
		return guess_for_x;
	}
	else {
		return BinarySubdivide(time, interval_start, interval_start + SAMPLES_STEP, _p1.x, _p2.x);
	}
}

bool BezierEasing::CheckPoints() const {
	return ((_p1.x >= 0 && _p1.x <= 1)
		&& (_p1.y >= 0 && _p1.y <= 1)
		&& (_p2.x >= 0 && _p2.x <= 1)
		&& (_p2.y >= 0 && _p2.y <= 1));
}
