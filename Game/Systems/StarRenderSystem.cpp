#include "StarRenderSystem.h"

#include <wtypes.h>
#include <GL/gl.h>

#include "../../Engine/Random/Random.h"
#include "../../Engine/Scene.h"
#include "../../Engine/Types/Color.h"

StarRenderSystem::StarRenderSystem(Color3 color) :
	_color(color)
{
	_stars.reserve(INIT_SIZE);

	for (auto i = 0; i < INIT_SIZE; i++)
	{
		_stars.emplace_back(Random::Next(0.f, Scene::scale.x * 2) - Scene::scale.x,
							Random::Next(0.f, Scene::scale.y * 2) - Scene::scale.y);
	}
}

void StarRenderSystem::SetStarsNumber(int number)
{
	const int oldSize = (int)_stars.size();
	
	_stars.resize(number);

	if (oldSize < number)
	{
		for(int i = oldSize; i < number; i++)
		{
			_stars[i].x = Random::Next(0.f, Scene::scale.x * 2) - Scene::scale.x;
			_stars[i].y = Random::Next(0.f, Scene::scale.y * 2) - Scene::scale.y;
		}
	}
}

void StarRenderSystem::SetColor(Color3 color)
{
	_color = color;
}

void StarRenderSystem::Run()
{
	glLoadIdentity();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPointSize(2.f);
	glBegin(GL_POINTS);
	
	for (auto&& star : _stars)
	{
		// Cathode-ray style blinking
		glColor4f(_color.red, _color.green, _color.blue, Random::Next(0.5f, 0.8f));
		glVertex2f(star.x, star.y);
	}

	glEnd();
}