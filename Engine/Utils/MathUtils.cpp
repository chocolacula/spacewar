#include "MathUtils.h"

#include <cmath>

const float MathUtils::ONE_RAD = 180.f / (float)M_PI;

float MathUtils::RadToDegree(float rads)
{
	return rads * ONE_RAD;
}

float MathUtils::DegreeToRad(float degrees)
{
	return degrees / ONE_RAD;
}
