#pragma once

#include "../../Engine/ECS/Component/Component.h"

class GravityBigObject final : public Component
{
public:
	GravityBigObject(Entity* entity, float mass, float range) :
		Component(entity),
		mass(mass),
		range(range)
	{}

	float mass;
	float range;
};