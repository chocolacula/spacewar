#include "EntityManager.h"
#include "Entity.h"

#include "../../Types/Transform.h"

Entity* EntityManager::FindEntity(int entityId)
{
	auto it = _entities.find(entityId);

	if (it == _entities.end())
		return nullptr;

	return it->second;
}

Entity* EntityManager::Create()
{
	const auto entity = new Entity();

	_entities[entity->GetID()] = entity;

	return entity;
}

Entity* EntityManager::Create(const Vector2& position)
{
	const auto entity = new Entity(position);

	_entities[entity->GetID()] = entity;

	return entity;
}

Entity* EntityManager::Create(const Transform& transform)
{
	const auto entity = new Entity(transform);

	_entities[entity->GetID()] = entity;

	return entity;
}

void EntityManager::Destroy(int entityId)
{
	auto it = _entities.find(entityId);

	if (it == _entities.end())
		return;

	delete it->second;
	_entities.erase(it);
}

void EntityManager::Destroy(const Entity* entity)
{
	Destroy(entity->GetID());
}
