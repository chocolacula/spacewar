#pragma once
#include "../../Engine/ECS/Component/Component.h"

class Projectile final : public Component
{
public:
	explicit Projectile(Entity* entity) :
		Component(entity),
		impulse(1.f)
	{}

	float impulse;
	// it could contain a damage value but one hit = death in our case
};