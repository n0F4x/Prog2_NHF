#pragma once


namespace math {
	extern const float PI;
}


float operator"" _deg(long double degree);
float operator"" _rad(long double radian);
float operator"" _deg(unsigned long long degree);
float operator"" _rad(unsigned long long radian);

namespace math {
	float convertToDeg(float radian);
}
