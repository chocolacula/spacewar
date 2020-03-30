#pragma once

#include "../../../Engine/ECS/System/ISystem.h"
#include "ProjectileSubSystem.h"

class UserInputSystem final : public ISystem, public ProjectileSubSystem 
{
public:
	void Run() override;
};
