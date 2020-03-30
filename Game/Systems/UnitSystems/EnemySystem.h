#pragma once

#include "../../../Engine/ECS/System/ISystem.h"
#include "ProjectileSubSystem.h"

class Enemy;
class Entity;

class EnemySystem final : public ISystem, public ProjectileSubSystem
{
public:
	void Run() override;

private:
	static void Move(Enemy* enemy);
	static void Stop(Entity* enemyEntity);
	static void Shot(Entity* enemyEntity);
	static void RotateFrom(Enemy* enemy, const Transform& target);
	static void RotateTo(Enemy* enemy, const Transform& target);

	const static float ENEMY_GRAVITY_THRESHOLD;
};
