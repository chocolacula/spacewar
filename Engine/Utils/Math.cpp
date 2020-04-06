#include "Math.h"

#include <corecrt_math_defines.h>

const float Math::ONE_RAD = 180.f / (float)M_PI;

float Math::RadToDegree(float rads)
{
	return rads * ONE_RAD;
}

float Math::DegreeToRad(float degrees)
{
	return degrees / ONE_RAD;
}
