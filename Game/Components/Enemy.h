#pragma once
#include "../../Engine/ECS/Component/Component.h"

class Enemy final : public Component
{
public:
	Enemy(Entity* entity) :
		Component(entity)
	{}

	float shotRange = 1.2f;
	float velocity = 0.8f;
	float angleVelocity = 75.f;
};
