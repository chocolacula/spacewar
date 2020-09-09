#pragma once

class MathUtils
{
public:
	MathUtils() = delete;

	static float RadToDegree(float rads);
	static float DegreeToRad(float degrees);

private:
	static const float ONE_RAD;
};