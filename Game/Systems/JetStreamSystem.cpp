#include "JetStreamSystem.h"

#include <wtypes.h>
#include <GL/gl.h>

#include "../../Engine/Engine.h"
#include "../../Engine/Scene.h"
#include "../../Engine/Utils/Math.h"
#include "../../Engine/Utils/Random.h"
#include "../Components/JetStreamParticles.h"

JetStreamSystem::JetStreamSystem(float updateTime) :
	_updateTime(updateTime),
	_deltaTime(0)
{}

void JetStreamSystem::Run()
{	
	auto jetStreams = Scene::GetComponentManager().FindAllComponents<JetStreamParticles>();

	JetStreamParticles* stream = nullptr;

	while(jetStreams.Next(stream))
	{
		Render(stream);
	}
}

void JetStreamSystem::Render(JetStreamParticles* particles)
{ 
	if (_deltaTime > _updateTime)
	{
		particles->_streamLengthNow = Random::Next(0.f, particles->streamLength);
		_deltaTime = Engine::DeltaTime();
	}
	else
	{
		_deltaTime += Engine::DeltaTime();
	}

	const auto transform = particles->GetEntity()->transform;
	
	glLoadIdentity();
	glTranslatef(transform.position.x, transform.position.y, 0.f);
	glRotatef(Math::RadToDegree(transform.angle), 0.f, 0.f, 1.f);

	glRotatef(90.f, 0, 0, 1);
	
	glLineWidth(3.f);
	glBegin(GL_LINES);
	glColor3f(particles->color.red, particles->color.green, particles->color.blue);
	
	glVertex2f(-0.015f, 0);
	glVertex2f(-0.015f, 0 + particles->_streamLengthNow * 0.75f);
	
	glVertex2f(0, 0);
	glVertex2f(0, 0 + particles->_streamLengthNow);

	glVertex2f(0.015f, 0);
	glVertex2f(0.015f, 0 + particles->_streamLengthNow * 0.75f);
	
	glEnd();
}
