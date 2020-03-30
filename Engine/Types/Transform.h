#pragma once

#include "Vector2.h"

struct Transform 
{
	Vector2 position;
	float angle;

	Transform();
	explicit Transform(Vector2 position);
	Transform(Vector2 position, float angle);
	
	Vector2 Forward() const;
	Vector2 Back() const;
	Vector2 Right() const;
	Vector2 Left() const;
};
