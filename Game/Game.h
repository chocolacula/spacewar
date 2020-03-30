#pragma once
#include "../Engine/ECS/Component/Embedded/Text.h"
#include "../Engine/ECS/Entity/Entity.h"

struct Ship
{
	Transform InitialTransform;
	Entity* ShipEntity;

	Ship() = default;

	Ship(const Transform& transform, Entity* entity) :
		InitialTransform(transform),
		ShipEntity(entity)
	{}
};

class Game
{
public:
	Game() = delete;
	
	static void Init();
	static void Reset();
	
private:
	static Text* _endOfGameText;

	static Ship					_userShip;
	static std::vector<Ship>	_enemyShips;
	
	static Entity* CreateWedge(const Transform& transform, int userColliderTag);
	static Entity* CreateNeedle(const Transform& transform);
	static void CreateGravityWell();
	static void CreateProjectilePool(int size);
	static void EndGame(bool isWin);
};
