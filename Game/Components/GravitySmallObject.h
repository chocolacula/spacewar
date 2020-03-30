#pragma once

#include "../../Engine/ECS/Component/Component.h"

class GravitySmallObject final : public Component
{
public:
	GravitySmallObject(Entity* entity) :
		Component(entity)
	{}
};