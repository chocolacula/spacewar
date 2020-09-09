#include "Types/Color.h"
#include "Scene.h"

#include "Engine.h"
#include "Game.h"

int main()
{
	Scene::clearColor = { 0, 0.05f, 0.12f, 0 };
	
	Game::Init();

	Engine::Run("Spacewar!", 1024, 768);
}
