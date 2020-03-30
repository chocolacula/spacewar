#pragma once
#include <vector>

#include "../../Engine/ECS/Component/Component.h"
#include "../../Engine/Types/Vector2.h"

struct Shard
{
	Vector2 position;
	std::vector<Vector2> triangles;

	Shard(const Vector2& position, std::vector<Vector2>&& triangles) :
		position(position),
		triangles(triangles)
	{}
};

class Blast final : public Component
{
public:
	explicit Blast(Entity* entity);
	Blast(Entity* entity, float impulse, float time);

	bool isBlasted = false;
	float impulse;
	float time;
	
	void AddShard(const Vector2& position, std::vector<Vector2>&& shardVertexes);

	std::vector<Shard>& GetShards();

private:
	std::vector<Shard> _shards;
};
