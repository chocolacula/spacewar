#include "Blast.h"

Blast::Blast(Entity* entity) :
	Component(entity),
	impulse(1),
	time(1)
{
	enabled = false;
}

Blast::Blast(Entity* entity, float impulse, float time) :
	Component(entity),
	impulse(impulse),
	time(time)
{
	enabled = false;
}

void Blast::AddShard(const Vector2& position, std::vector<Vector2>&& shardVertexes)
{
	_shards.emplace_back(position, std::move(shardVertexes));
}

std::vector<Shard>& Blast::GetShards()
{
	return _shards;
}
