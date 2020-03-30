#pragma once
#include "../../Engine/ECS/System/ISystem.h"

class JetStreamParticles;
struct Transform;

class JetStreamSystem final : public ISystem
{
public:
	JetStreamSystem(float updateTime);
	
	void Run() override;

private:
	void Render(JetStreamParticles* particles);

	float _updateTime;
	float _deltaTime;
};
