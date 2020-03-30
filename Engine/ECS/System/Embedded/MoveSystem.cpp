#include "MoveSystem.h"

#include "../../../Engine.h"
#include "../../../Scene.h"
#include "../../Component/Embedded/Velocity.h"
#include "../../Entity/Entity.h"

void MoveSystem::Run()
{
	auto velocities = Scene::GetComponentManager().FindAllComponents<Velocity>();

	Velocity* velocity = nullptr;

	while (velocities.Next(velocity))
	{
		auto entity = velocity->GetEntity();
		
		entity->transform.position = entity->transform.position + velocity->value * Engine::DeltaTime();
	}
}
