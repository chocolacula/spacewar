#include "EntityManager.h"
#include "Entity.h"

#include "../../Types/Transform.h"

Entity* EntityManager::FindEntity(Entity* entity)
{
	const auto it = _entities.find(entity);

	if (it == _entities.end())
		return nullptr;

	return *it;
}

Entity* EntityManager::Create()
{
	const auto entity = new Entity();

	_entities.insert(entity);

	return entity;
}

Entity* EntityManager::Create(const Vector2& position)
{
	const auto entity = new Entity(position);

	_entities.insert(entity);

	return entity;
}

Entity* EntityManager::Create(const Transform& transform)
{
	const auto entity = new Entity(transform);

	_entities.insert(entity);

	return entity;
}

void EntityManager::Destroy(Entity* entity)
{
	const auto it = _entities.find(entity);

	if (it == _entities.end())
		return;

	delete *it;
	_entities.erase(it);
}
