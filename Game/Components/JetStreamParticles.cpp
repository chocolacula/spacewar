#include "JetStreamParticles.h"

JetStreamParticles::JetStreamParticles(Entity* entity) :
	Component(entity),
	color(Color3::LIGHT_BLUE),
	streamLength(0.25)
{
	enabled = false;
}

JetStreamParticles::JetStreamParticles(Entity* entity, Color3 color, float streamLength, float sparksTime) :
	Component(entity),
	color(color),
	streamLength(streamLength)
{
	enabled = false;
}