#pragma once
#include "../../Engine/ECS/System/ISystem.h"

class CollisionSystem final : public ISystem
{
	void Run() override;
};