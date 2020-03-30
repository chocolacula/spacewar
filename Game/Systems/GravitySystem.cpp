#include "GravitySystem.h"

#include "../../Engine/ECS/Component/Embedded/Velocity.h"
#include "../../Engine/Scene.h"
#include "../Components/GravityBigObject.h"
#include "../Components/GravitySmallObject.h"

void GravitySystem::Run()
{
	auto bigs = Scene::GetComponentManager().FindAllComponents<GravityBigObject>();
	auto smalls = Scene::GetComponentManager().FindAllComponents<GravitySmallObject>();
	
	GravityBigObject* big = nullptr;
	GravitySmallObject* small = nullptr;
	
	while (bigs.Next(big))
	{
		const auto objectTransform = big->GetEntity()->transform;

		while (smalls.Next(small))
		{
			auto subjectVelocity = small->GetEntity()->GetComponent<Velocity>();

			if (subjectVelocity == nullptr)
				continue;

			const auto subjectTransform = small->GetEntity()->transform;
			
			auto const deltaVector = objectTransform.position - subjectTransform.position;
			auto const deltaLength = deltaVector.Length();

			if (deltaLength > big->range)
				continue;
					
			auto const effect = (big->range - deltaLength) / big->range;

			auto const deltaX = deltaVector.x / deltaLength;
			auto const deltaY = deltaVector.y / deltaLength;

			// add velocity with direction to the gravity well
			subjectVelocity->value += Vector2(deltaX, deltaY) * big->mass * effect;

			// add a little bit of velocity with direction 90 degree to the right
			// because realistic behaviour isn't fun 
			subjectVelocity->value += Vector2(-deltaY, deltaX) * (big->mass * effect / 6);
		}
	}
}
