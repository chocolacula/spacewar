#pragma once
#include "../../Engine/ECS/System/ISystem.h"

class GravitySystem final : public ISystem
{
public:
	void Run() override;

private:
	static const float SPIN_FACTOR;
};
