#include "Angle.hpp"

#include <numbers>


extern const float math::PI = std::numbers::pi_v<float>;


float operator"" _deg(long double degree) {
	return static_cast<float>(degree) * math::PI / 180.f;
}

float operator"" _rad(long double radian) {
	return static_cast<float>(radian);
}

float operator"" _deg(unsigned long long degree) {
	return static_cast<float>(degree) * math::PI / 180.f;
}

float operator"" _rad(unsigned long long radian) {
	return static_cast<float>(radian);
}

namespace math {
	float convertToDeg(float radian) {
		return radian * 180.f / math::PI;
	}
}
