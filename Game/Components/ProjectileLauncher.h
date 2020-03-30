#pragma once
#include "../../Engine/ECS/Component/Component.h"

class ProjectileLauncher final : public Component
{
public:
	explicit ProjectileLauncher(Entity* entity) :
		Component(entity),
		coolDown(1.f),
		timeNow(0)
	{}

	float coolDown;
	float timeNow;
};