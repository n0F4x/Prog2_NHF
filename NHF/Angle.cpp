#include "Angle.hpp"


float operator"" _deg(long double degree) {
	return static_cast<float>(degree) * 3.14159265f / 180.f;
}

float operator"" _rad(long double radian) {
	return static_cast<float>(radian);
}

float operator"" _deg(unsigned long long degree) {
	return static_cast<float>(degree) * 3.14159265f / 180.f;
}

float operator"" _rad(unsigned long long radian) {
	return static_cast<float>(radian);
}
