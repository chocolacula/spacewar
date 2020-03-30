#pragma once

#include "ECS/Entity/EntityManager.h"
#include "ECS/Component/ComponentManager.h"
#include "ECS/System/SystemManager.h"

struct Color4;
struct Vector2;

class Scene
{
public:
	Scene() = delete;

	static Color4 clearColor;
	static Vector2 scale;
	
	static EntityManager& GetEntityManager();
	static ComponentManager& GetComponentManager();
	static SystemManager& GetSystemManager();

private:
	static EntityManager _entityManager;
	static ComponentManager _componentManager;
	static SystemManager _systemManager;
};