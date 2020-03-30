#pragma once
#include "../../Engine/ECS/Component/Component.h"

class User final : public Component
{
public:
	User(Entity* entity) :
		Component(entity)
	{}
};
