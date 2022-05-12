#pragma once


namespace math {
	extern const float PI;
}


float operator"" _deg(long double degree);
float operator"" _deg(unsigned long long degree);

namespace math {
	float convertToDeg(float radian);
}
