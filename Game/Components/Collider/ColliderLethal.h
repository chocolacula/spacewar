#pragma once
#include "Collider.h"

class ColliderLethal final : public Collider
{
public:
	ColliderLethal(Entity* entity) :
		Collider(entity, 0.5f, 0)
	{}

	ColliderLethal(Entity* entity, float range, int tag) :
		Collider(entity, range, tag)
	{}
};
