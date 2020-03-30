#include "BlastSystem.h"

#include "../../Engine/ECS/Component/Embedded/Mesh.h"
#include "../../Engine/ECS/Component/Embedded/Velocity.h"
#include "../../Engine/ECS/Entity/Entity.h"
#include "../../Engine/Math.h"
#include "../../Engine/Scene.h"
#include "../Components/Blast.h"
#include "../Components/Collider/ColliderTarget.h"
#include "../Components/GravitySmallObject.h"
#include "../Components/LifeTime.h"
#include "../Components/Rotor.h"

void BlastSystem::Run()
{
	auto targets = Scene::GetComponentManager().FindAllComponents<ColliderTarget>();

	ColliderTarget* target = nullptr;

	while (targets.Next(target))
	{
		if (!target->isHit)
			continue;

		auto entity = target->GetEntity();
		auto blast = entity->GetComponent<Blast>();

		if (blast->isBlasted)
			continue;
		
		entity->enabled = false;

		const auto shardsNumber = blast->GetShards().size();
		auto angle = 360.f / shardsNumber;

		for (auto&& shard : blast->GetShards())
		{
			auto shardEntity = Scene::GetEntityManager().Create(entity->transform.position + shard.position);

			shardEntity->AddComponent<Mesh>()
				->SetTriangles(std::move(shard.triangles));

			shardEntity->AddComponent<Velocity>()
				->value = Vector2(Math::DegreeToRad(angle) * blast->impulse)
					+ entity->GetComponent<Velocity>()->value;

			shardEntity->AddComponent<GravitySmallObject>();
			
			shardEntity->AddComponent<Rotor>(2.2f);
			shardEntity->AddComponent<LifeTime>(4.f);

			angle += angle;
		}

		blast->isBlasted = true;
	}
}
