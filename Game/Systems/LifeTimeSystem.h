#pragma once
#include "../../Engine/ECS/System/ISystem.h"

class LifeTimeSystem final : public ISystem
{
	void Run() override;
};
