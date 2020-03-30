#include "LifeTimeSystem.h"

#include "../../Engine/Engine.h"
#include "../../Engine/Scene.h"
#include "../Components/LifeTime.h"

void LifeTimeSystem::Run()
{
	auto times = Scene::GetComponentManager().FindAllComponents<LifeTime>();

	LifeTime* time = nullptr;
	
	while (times.Previous(time))
	{
		if (time->timeNow >= time->timeMax)
		{
			if (!time->isDisposable)
			{
				time->timeNow = 0;
				time->GetEntity()->enabled = false;
			}
			else
			{
				Scene::GetEntityManager().Destroy(time->GetEntity());
			}
		}
		else
		{
			time->timeNow += Engine::DeltaTime();
		}
	}	
}
