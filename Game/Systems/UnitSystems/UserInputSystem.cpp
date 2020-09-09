#include "UserInputSystem.h"

#include "../../../Engine/ECS/Component/Embedded/Velocity.h"
#include "../../../Engine/Engine.h"
#include "Input/Input.h"
#include "../../../Engine/Scene.h"
#include "../../Components/Collider/ColliderTarget.h"
#include "../../Components/JetStreamParticles.h"
#include "../../Components/ProjectileLauncher.h"
#include "../../Components/User.h"
#include "../../Game.h"

void UserInputSystem::Run()
{
	auto inputs = Scene::GetComponentManager().FindAllComponents<User>();

	User* input = nullptr;

	while (inputs.Next(input, true))
	{
		auto entity = input->GetEntity();
		auto& transform = entity->transform;

		if (Input::GetKeyDown() == Keyboard::W)
		{
			const auto velocity = entity->GetComponent<Velocity>();
			velocity->value = transform.Forward();

			const auto jetStream = entity->GetComponent<JetStreamParticles>();
			jetStream->enabled = true;
		}

		if (Input::GetKeyUp() == Keyboard::W)
		{
			const auto jetStream = entity->GetComponent<JetStreamParticles>();
			jetStream->enabled = false;
		}

		transform.angle = (Input::GetMousePosition() - transform.position).Angle();

		if (Input::GetKeyDown() == Keyboard::Space)
		{
			Game::Reset();
		}

		auto launcher = entity->GetComponent<ProjectileLauncher>();

		auto a = Input::GetMouseButtonDown();
		if (a == Mouse::Button1 && launcher->timeNow >= launcher->coolDown)
		{
			LaunchProjectile(transform, entity->GetComponent<ColliderTarget>()->tag);
			launcher->timeNow = 0;
		}

		launcher->timeNow += Engine::DeltaTime();
	}
}
