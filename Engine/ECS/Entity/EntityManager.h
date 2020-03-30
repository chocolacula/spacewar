#pragma once

#include <unordered_map>

struct Transform;
struct Vector2;
class Entity;

class EntityManager
{
public:
	Entity* FindEntity(int entityId);
	Entity* Create();
	Entity* Create(const Vector2& position);
	Entity* Create(const Transform& transform);

	void Destroy(int entityId);
	void Destroy(const Entity* entity);

private:
	std::unordered_map<int, Entity*> _entities;
};