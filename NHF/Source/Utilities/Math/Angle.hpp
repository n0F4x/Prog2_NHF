#pragma once


namespace math {
	extern const float PI;
}


/**
 * @brief	operator for conversion from degrees to radians
*/
float operator"" _deg(long double degree);
/**
 * @brief	operator for conversion from degrees to radians
*/
float operator"" _deg(unsigned long long degree);

namespace math {
	/**
	 * @brief	Converts the given value from radians to degrees
	 * @param radian	The value for in radians
	 * @return	The value in degrees
	*/
	float convertToDeg(float radian);
}
