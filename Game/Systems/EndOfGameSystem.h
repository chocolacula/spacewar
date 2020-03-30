#pragma once
#include <functional>

#include "../../Engine/ECS/System/ISystem.h"

class EndOfGameSystem final : public ISystem
{
public:
	EndOfGameSystem(int userColliderTag, std::function<void(bool)> endCallback);
	void Run() override;

private:
	int _userColliderTag;
	std::function<void(bool)> _endCallback;
};
