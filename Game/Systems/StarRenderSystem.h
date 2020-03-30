#pragma once
#include <vector>

#include "../../Engine/ECS/System/ISystem.h"
#include "../../Engine/Types/Color.h"
#include "../../Engine/Types/Vector2.h"

class StarRenderSystem : ISystem
{
public:
	StarRenderSystem(Color3 color);
	
	void SetStarsNumber(int number);
	void SetColor(Color3 color);
	void Run() override;

private:
	std::vector<Vector2> _stars;
	Color3 _color = Color3::LIGHT_BLUE;
	const int INIT_SIZE = 100;
};

