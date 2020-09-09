#include "Vector2.h"
#include <cmath>

#include "Polar.h"

const Vector2 Vector2::ZERO = { 0, 0 };
const Vector2 Vector2::ONE  = { 1, 1 };

Vector2::Vector2() :
	x(0),
	y(0)
{}

Vector2::Vector2(float angle) :
	x(std::cos(angle)),
	y(std::sin(angle))
{}

Vector2::Vector2(float x, float y) :
	x(x),
	y(y)
{}

Vector2::Vector2(const Polar& polar) :
	Vector2(Vector2(polar.angle) * polar.length)
{}

float Vector2::DotProduct(const Vector2& other) const
{
	return x * other.x + y * other.y;
}

float Vector2::Length() const
{
	return std::sqrt(DotProduct(*this));
}

float Vector2::Angle() const
{
	return std::atan2(y, x);
}

Vector2 Vector2::Normalize() const
{
	const auto l = Length();
	return {x / l, y / l};
}

bool Vector2::operator== (Vector2 const& right) const
{
	return x == right.x && y == right.y;
}

bool Vector2::operator!= (Vector2 const& right) const
{
	return x != right.x || y != right.y;
}

Vector2 Vector2::operator+= (Vector2 const& right)
{
	x += right.x;
	y += right.y;

	return *this;
}

Vector2 Vector2::operator+= (float scalar)
{
	x += scalar;
	y += scalar;

	return *this;
}

Vector2 Vector2::operator-= (Vector2 const& right)
{
	x -= right.x;
	y -= right.y;

	return *this;
}

Vector2 Vector2::operator-= (float scalar)
{
	x -= scalar;
	y -= scalar;

	return *this;
}

Vector2 Vector2::operator*= (float scalar)
{
	x *= scalar;
	y *= scalar;

	return *this;
}

Vector2 Vector2::operator/= (float scalar)
{
	x /= scalar;
	y /= scalar;

	return *this;
}

Vector2 operator+ (Vector2 const& left, Vector2 const& right)
{
	return {left.x + right.x, left.y + right.y};
}

Vector2 operator+ (Vector2 const& left, float scalar)
{
	return {left.x + scalar, left.y + scalar};
}

Vector2 operator- (Vector2 const& left, Vector2 const& right)
{
	return {left.x - right.x, left.y - right.y};
}

Vector2 operator- (Vector2 const& left, float scalar)
{
	return {left.x - scalar, left.y - scalar};
}

Vector2 operator* (Vector2 const& left, float scalar)
{
	return {left.x * scalar, left.y * scalar};
}

Vector2 operator* (float scalar, Vector2 const& left)
{
	return {left.x * scalar, left.y * scalar};
}

Vector2 operator/(const Vector2& left, float scalar)
{
	return { left.x / scalar, left.y / scalar };
}

Vector2 operator/(float scalar, const Vector2& left)
{
	return { left.x / scalar, left.y / scalar };
}
