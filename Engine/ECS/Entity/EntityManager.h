#pragma once

#include <unordered_set>

struct Transform;
struct Vector2;
class Entity;

class EntityManager
{
public:
	Entity* FindEntity(Entity* entity);
	Entity* Create();
	Entity* Create(const Vector2& position);
	Entity* Create(const Transform& transform);
	
	void Destroy(Entity* entity);

private:
	std::unordered_set<Entity*> _entities;
};