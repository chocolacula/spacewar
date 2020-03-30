#pragma once
#include "../../Engine/ECS/System/ISystem.h"

class GravitySystem final : public ISystem
{
	void Run() override;
};
