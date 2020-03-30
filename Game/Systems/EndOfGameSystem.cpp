#include "EndOfGameSystem.h"

#include <utility>

#include "../../Engine/Scene.h"
#include "../Components/Collider/ColliderTarget.h"

EndOfGameSystem::EndOfGameSystem(int userColliderTag, std::function<void(bool)> endCallback) :
	_userColliderTag(userColliderTag),
	_endCallback(std::move(endCallback))
{}

void EndOfGameSystem::Run()
{	
	auto targets = Scene::GetComponentManager().FindAllComponents<ColliderTarget>();

	ColliderTarget* target = nullptr;

	auto enemies = 0;
	auto isPlayerDied = true;
	
	while (targets.Next(target))
	{
		if (target->tag == _userColliderTag)
			isPlayerDied = false;
		else
			enemies++;
	}

	if (isPlayerDied)
	{
		// the player has died = fail
		_endCallback(false);
	}
	else if (enemies == 0)
	{
		// the player is alive and no more enemies = win
		_endCallback(true);
	}
}