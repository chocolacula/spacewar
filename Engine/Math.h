#pragma once

class Math
{
public:
	Math() = delete;

	static float RadToDegree(float rads);
	static float DegreeToRad(float degrees);

private:
	static const float ONE_RAD;
};