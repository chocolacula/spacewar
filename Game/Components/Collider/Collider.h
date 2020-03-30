#pragma once
#include "../../../Engine/ECS/Component/Component.h"

class Collider : public Component
{
public:
	Collider(Entity* entity) :
		Component(entity),
		range(0.5),
		tag(0)
	{}

	Collider(Entity* entity, float range, int tag) :
		Component(entity),
		range(range),
		tag(tag)
	{}

	float range;
	int tag;
};
