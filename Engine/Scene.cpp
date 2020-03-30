#include "Scene.h"

#include "Types/Color.h"
#include "Types/Vector2.h"

Color4  Scene::clearColor = Color4::BLACK;
Vector2 Scene::scale      = {3, 3};

EntityManager		Scene::_entityManager;
ComponentManager	Scene::_componentManager;
SystemManager		Scene::_systemManager;

EntityManager& Scene::GetEntityManager()
{
	return _entityManager;
}

ComponentManager& Scene::GetComponentManager()
{
	return _componentManager;
}

SystemManager& Scene::GetSystemManager()
{
	return _systemManager;
}