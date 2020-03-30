#include "RotorSystem.h"

#include "../../Engine/Engine.h"
#include "../../Engine/Scene.h"
#include "../Components/Rotor.h"

void RotorSystem::Run()
{
	auto rotors = Scene::GetComponentManager().FindAllComponents<Rotor>();

	Rotor* rotor = nullptr;

	while (rotors.Next(rotor))
	{
		Transform& transform = rotor->GetEntity()->transform;

		transform.angle += rotor->angleVelocity * Engine::DeltaTime();
	}
}
