#pragma once
#include "../../Engine/ECS/Component/Component.h"

class LifeTime final : public Component
{
public:
	LifeTime(Entity* entity, float time) :
		Component(entity),
		timeMax(time)
	{}

	float timeMax;
	float timeNow = 0;
	bool isDisposable = true;
};
