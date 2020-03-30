#include <Windows.h>

#include "../Engine/Types/Color.h"
#include "../Engine/Scene.h"

#include "../Engine/Engine.h"
#include "Game.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	Scene::clearColor = { 0, 0.05f, 0.12f, 0 };
	
	Game::Init();

	Engine::Run("Spacewar!", 1024, 768);
}
