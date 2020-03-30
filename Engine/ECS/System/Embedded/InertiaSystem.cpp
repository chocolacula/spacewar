#include "InertiaSystem.h"

#include "../../../Engine.h"
#include "../../../Scene.h"
#include "../../Component/Embedded/Velocity.h"

void InertiaSystem::Run()
{
	auto velocities = Scene::GetComponentManager().FindAllComponents<Velocity>();

	Velocity* velocity = nullptr;
	
	while (velocities.Next(velocity))
	{
		auto const length = velocity->value.Length();
		
		 if (length > 0)
			 velocity->value *= (1.f - velocity->drag * Engine::DeltaTime() / length);
	}
}
