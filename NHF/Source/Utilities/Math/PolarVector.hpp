#pragma once


/**
 * @brief	Struct for representing a vector in polar coordinates
*/
struct PolarVector {
	float radius;
	float angle;
	PolarVector(float radius_ = 0, float angle_ = 0) : radius{ radius_ }, angle{ angle_ } {}
};
