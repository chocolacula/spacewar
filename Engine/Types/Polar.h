#pragma once

struct Vector2;

struct Polar
{
	float angle;
	float length;

	Polar();
	explicit Polar(float angle);
	Polar(float angle, float length);
	explicit Polar(const Vector2& vector);
};
