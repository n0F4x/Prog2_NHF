#pragma once


class Angle {
private:
	float _angle;

public:
	Angle(float angle = 0);
	operator float() const;
	friend Angle operator"" _deg(long double degree);
	friend Angle operator"" _rad(long double radian);
	friend Angle operator"" _deg(unsigned long long);
	friend Angle operator"" _rad(unsigned long long);
	Angle& operator+=(const Angle& rhs);
	Angle& operator-=(const Angle& rhs);
};

Angle operator"" _deg(long double degree);
Angle operator"" _rad(long double radian);
Angle operator"" _deg(unsigned long long degree);
Angle operator"" _rad(unsigned long long radian);
