#pragma once
#include "../ISystem.h"

class InertiaSystem final : public ISystem
{
public:	
	void Run() override;
};