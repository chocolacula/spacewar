#pragma once

struct Polar;

struct Vector2
{
	float x;
	float y;
	
	Vector2();
	explicit Vector2(float angle);
	Vector2(float x, float y);
	explicit Vector2(const Polar& polar);
	
	float DotProduct(const Vector2& other) const;
	float Length() const;
	float Angle() const;
	Vector2 Normalize() const;

	bool operator== (const Vector2& right) const;
	bool operator!= (const Vector2& right) const;

	Vector2 operator+= (const Vector2& right);
	Vector2 operator+= (float scalar);

	Vector2 operator-= (const Vector2& right);
	Vector2 operator-= (float scalar);

	Vector2 operator*= (float scalar);
	Vector2 operator/=(float scalar);

	static const Vector2 ZERO;
	static const Vector2 ONE;
};

Vector2 operator+ (const Vector2& left, const Vector2& right);
Vector2 operator+ (const Vector2& left, float scalar);

Vector2 operator- (const Vector2& left, const Vector2& right);
Vector2 operator- (const Vector2& left, float scalar);

Vector2 operator* (const Vector2& left, float scalar);
Vector2 operator* (float scalar, const Vector2& left);

Vector2 operator/ (const Vector2& left, float scalar);
Vector2 operator/ (float scalar, const Vector2& left);

