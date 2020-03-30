#pragma once

#include "../../Engine/ECS/Component/Component.h"
#include "../../Engine/Types/Color.h"

class JetStreamParticles final : public Component
{
public:
	JetStreamParticles(Entity* entity);
	JetStreamParticles(Entity* entity, Color3 color, float streamLength, float sparksTime);
	
	Color3 color;
	float streamLength;
	
private:
	float _streamLengthNow;
	
	friend class JetStreamSystem;
};
