#include "Angle.hpp"


Angle::Angle(float angle) : _angle{ angle } {}

Angle::operator float() const {
	return _angle;
}

Angle& Angle::operator+=(const Angle& rhs) {
	_angle += rhs;
	return *this;
}

Angle& Angle::operator-=(const Angle& rhs) {
	_angle -= rhs;
	return *this;
}

Angle operator"" _deg(long double degree) {
	return Angle{ static_cast<float>(degree) * 3.14159265f / 180.f };
}

Angle operator"" _rad(long double radian) {
	return Angle{ static_cast<float>(radian) };
}

Angle operator"" _deg(unsigned long long degree) {
	return Angle{ static_cast<float>(degree) * 3.14159265f / 180.f };
}

Angle operator"" _rad(unsigned long long radian) {
	return Angle{ static_cast<float>(radian) };
}
