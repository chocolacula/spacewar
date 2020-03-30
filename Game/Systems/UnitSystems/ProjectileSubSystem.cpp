#include "ProjectileSubSystem.h"

#include "../../../Engine/ECS/Entity/Entity.h"
#include "../../../Engine/ECS/Component/Embedded/Velocity.h"
#include "../../../Engine/Scene.h"
#include "../../Components/Collider/ColliderLethal.h"
#include "../../Components/Projectile.h"

void ProjectileSubSystem::LaunchProjectile(const Transform& transform, int tag)
{
	auto projectiles = Scene::GetComponentManager().FindAllComponents<Projectile>();
	Projectile* projectile = nullptr;

	while (projectiles.Next(projectile, true))
	{
		auto entity = projectile->GetEntity();

		if (!entity->enabled)
		{
			entity->transform = transform;
			entity->GetComponent<ColliderLethal>()->tag = tag;
			entity->GetComponent<Velocity>()->value = transform.Forward() * projectile->impulse;
			entity->enabled = true;

			break;
		}
	}
}
