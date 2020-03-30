#include "CollisionSystem.h"

#include "../../Engine/ECS/Entity/Entity.h"
#include "../../Engine/Scene.h"
#include "../Components/Blast.h"
#include "../Components/Collider/ColliderLethal.h"
#include "../Components/Collider/ColliderTarget.h"

void CollisionSystem::Run()
{
	auto targets = Scene::GetComponentManager().FindAllComponents<ColliderTarget>();
	auto lethals = Scene::GetComponentManager().FindAllComponents<ColliderLethal>();

	ColliderTarget* target = nullptr;
	ColliderLethal* lethal = nullptr;

	while (targets.Next(target))
	{
		auto targetPosition = target->GetEntity()->transform.position;
		
		while (lethals.Next(lethal))
		{
			auto lethalPosition = lethal->GetEntity()->transform.position;

			const auto delta = (lethalPosition - targetPosition).Length();

			auto a = target->tag != lethal->tag;
			
			if (target->tag != lethal->tag && delta <= target->range / 2 + lethal->range / 2)
				target->isHit = true;
		}
	}
}
