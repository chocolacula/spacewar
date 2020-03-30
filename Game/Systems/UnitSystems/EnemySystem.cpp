#include "EnemySystem.h"

#include "../../../Engine/ECS/Component/Embedded/Velocity.h"
#include "../../../Engine/Engine.h"
#include "../../../Engine/Math.h"
#include "../../../Engine/Scene.h"
#include "../../Components/Collider/ColliderTarget.h"
#include "../../Components/Enemy.h"
#include "../../Components/GravityBigObject.h"
#include "../../Components/JetStreamParticles.h"
#include "../../Components/ProjectileLauncher.h"
#include "../../Components/User.h"

const float EnemySystem::ENEMY_GRAVITY_THRESHOLD = 0.3f;

void EnemySystem::Run()
{
	auto users = Scene::GetComponentManager().FindAllComponents<User>();
	auto enemies = Scene::GetComponentManager().FindAllComponents<Enemy>();

	User* user = nullptr;
	Enemy* enemy = nullptr;

	// The only one user
	users.Next(user);

	if (user == nullptr)
		return;
	
	while (enemies.Next(enemy))
	{
		const auto enemyEntity = enemy->GetEntity();
		
		// Perception model
		auto isGravityDanger = false;
		auto isUserNear = false;
		
		auto bigs = Scene::GetComponentManager().FindAllComponents<GravityBigObject>();

		GravityBigObject* big = nullptr;

		while (bigs.Next(big))
		{
			const auto delta = (big->GetEntity()->transform.position 
									  - enemy->GetEntity()->transform.position).Length();

			if (delta < big->range * ENEMY_GRAVITY_THRESHOLD)
			{
				// take first, in our case it is the only one
				isGravityDanger = true;
				break;
			}
		}

		{
			const auto delta = (user->GetEntity()->transform.position
									   - enemy->GetEntity()->transform.position).Length();

			isUserNear = delta <= enemy->shotRange;
		}

		// A little behaviour tree with actions for each branch
		// implemented Thinking and Action models
		if (isGravityDanger)
		{
			Move(enemy);
			RotateFrom(enemy, big->GetEntity()->transform);
		}
		else
		{
			if (isUserNear)
			{
				Stop(enemyEntity);
				Shot(enemyEntity);
				RotateTo(enemy, user->GetEntity()->transform);
			}
			else
			{
				Move(enemy);
				Shot(enemyEntity);
				RotateTo(enemy, user->GetEntity()->transform);
			}
		}
	}
}

void EnemySystem::Move(Enemy* enemy)
{
	const auto entity = enemy->GetEntity();
	const auto jetStream = entity->GetComponent<JetStreamParticles>();
	const auto velocity = entity->GetComponent<Velocity>();
	velocity->value = entity->transform.Forward() * enemy->velocity;

	jetStream->enabled = true;
}

void EnemySystem::Stop(Entity* enemyEntity)
{
	const auto jetStream = enemyEntity->GetComponent<JetStreamParticles>();
	jetStream->enabled = false;
}

void EnemySystem::Shot(Entity* enemyEntity)
{
	auto launcher = enemyEntity->GetComponent<ProjectileLauncher>();

	if (launcher->timeNow >= launcher->coolDown)
	{
		LaunchProjectile(enemyEntity->transform, enemyEntity->GetComponent<ColliderTarget>()->tag);
		launcher->timeNow = 0;
	}
	else
	{
		launcher->timeNow += Engine::DeltaTime();
	}
}

void EnemySystem::RotateFrom(Enemy* enemy, const Transform& target)
{
	auto& enemyTransform = enemy->GetEntity()->transform;
	const auto delta = target.position - enemyTransform.position;
	const auto dotProduct = delta.DotProduct(enemyTransform.Left());
	
	if (dotProduct > 0)
	{
		// turn right
		enemyTransform.angle -= Math::DegreeToRad(enemy->angleVelocity) * Engine::DeltaTime();
	}
	else
	{
		// turn left		
		enemyTransform.angle += Math::DegreeToRad(enemy->angleVelocity) * Engine::DeltaTime();
	}
}

void EnemySystem::RotateTo(Enemy* enemy, const Transform& target)
{
	auto& enemyTransform = enemy->GetEntity()->transform;
	enemyTransform.angle = (target.position - enemyTransform.position).Angle();
}
