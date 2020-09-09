#include "Transform.h"

#include <cmath>

Transform::Transform() :
	position(Vector2::ZERO),
	angle(0)
{}

Transform::Transform(Vector2 position) :
	position(position),
	angle(0)
{}

Transform::Transform(Vector2 position, float angle) :
	position(position),
	angle(angle)
{}

Vector2 Transform::Forward() const
{
	return Vector2(angle);
}

Vector2 Transform::Back() const
{
	return Vector2(angle + (float)M_PI);
}

Vector2 Transform::Right() const
{
	return Vector2(angle - (float)M_PI_2);
}

Vector2 Transform::Left() const
{
	return Vector2(angle + (float)M_PI_2);
}
