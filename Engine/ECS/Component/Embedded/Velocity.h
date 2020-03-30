#pragma once
#include "../../../Types/Vector2.h"
#include "../Component.h"

class Velocity final : public Component
{
public:
	Velocity(Entity* entity);

	Vector2 value = Vector2::ZERO;
	float drag = 0.5f;
};