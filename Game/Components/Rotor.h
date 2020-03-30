#pragma once
#include "../../Engine/ECS/Component/Component.h"

class Rotor final : public Component
{
public:
	Rotor(Entity* entity, float angleVelocity) :
		Component(entity),
		angleVelocity(angleVelocity)
	{}

	float angleVelocity;
};
