#pragma once
#include "../ISystem.h"

class MoveSystem final : public ISystem
{
public:
	void Run() override;
};