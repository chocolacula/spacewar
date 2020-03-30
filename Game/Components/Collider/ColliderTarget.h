#pragma once
#include "Collider.h"

class ColliderTarget final : public Collider
{
public:
	ColliderTarget(Entity* entity) :
		Collider(entity, 0.5f, 0),
		isHit(false)
	{}

	ColliderTarget(Entity* entity, float range, int tag) :
		Collider(entity, range, tag),
		isHit(false)
	{}

	bool isHit;
};
