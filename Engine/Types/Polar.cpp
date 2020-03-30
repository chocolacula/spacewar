#include "Polar.h"
#include "Vector2.h"

Polar::Polar() :
	angle(0),
	length(0)
{}

Polar::Polar(float angle) :
	angle(angle),
	length(1)
{}

Polar::Polar(float angle, float length) :
	angle(angle),
	length(length)
{}

Polar::Polar(const Vector2& vector) :
	angle(vector.Angle()),
	length(vector.Length())
{}
