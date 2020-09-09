#include "Engine.h"

#include <cassert>
#include <iostream>

#include "Scene.h"
#include "Types/Color.h"

#include "Input/Input.h"
#include "ECS/System/SystemManager.h"
#include "Types/Vector2.h"

int	   Engine::_windowWidth  = 0;
int	   Engine::_windowHeight = 0;
int	   Engine::_maxFPS       = 60;
float  Engine::_deltaTime    = 0;
double Engine::_lastTime     = 0;

GLFWwindow* Engine::_window = nullptr;

//HGLRC Engine::_openGLHandle = nullptr;
//HWND Engine::_windowHandle = nullptr;

void Engine::Run(const char* name, int windowWidth, int windowHeight)
{
	Init(name, windowWidth, windowHeight);

	MainLoop();

//	ResetOpenGL();

    glfwDestroyWindow(_window);
    glfwTerminate();
}

void Engine::MainLoop()
{
    while (!glfwWindowShouldClose(_window))
    {
        // lock fps
        while (true)
        {
            auto now = glfwGetTime();
            auto deltaTime = now - _lastTime;

            if (deltaTime >= 1.0 / _maxFPS)
            {
                _deltaTime = (float)deltaTime;
                _lastTime = now;

                break;
            }
        }

        // get input
        Input::Reset();
        glfwPollEvents();

        // do logic
        // Handle all systems
//        Scene::GetSystemManager().HandleAllSystems();

        // render on the screen
        RenderNextFrame();
    }
}

int Engine::GetWindowWidth()
{
	return _windowWidth;
}

int Engine::GetWindowHeight()
{
	return _windowHeight;
}

float Engine::DeltaTime()
{
	return _deltaTime;
}

int Engine::SetMaxFPS(int maxFPS)
{
	return _maxFPS = maxFPS;
}

void Engine::Init(const char* name, int windowWidth, int windowHeight)
{
	_windowWidth = windowWidth;
	_windowHeight = windowHeight;

	InitWindow(name, windowWidth, windowHeight);

	glfwSetKeyCallback(_window, Input::key_callback);
	glfwSetMouseButtonCallback(_window, Input::mouse_button_callback);
	glfwSetScrollCallback(_window, Input::scroll_callback);
	glfwSetCursorPosCallback(_window, Input::cursor_position_callback);

	InitOpenGL();
}

void Engine::InitWindow(const char* name, int windowWidth, int windowHeight)
{
	glfwInit();
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	_window = glfwCreateWindow(windowWidth, windowHeight, name, nullptr, nullptr);

	glfwMakeContextCurrent(_window);
}

void Engine::InitOpenGL()
{
	glClearColor(Scene::clearColor.red, Scene::clearColor.green, Scene::clearColor.blue, Scene::clearColor.alpha);
}

void Engine::RenderNextFrame()
{
	// Reset render data
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glScalef(1 / Scene::scale.x, 1 / Scene::scale.y, 0.f);

	glDisable(GL_CULL_FACE);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	Scene::GetSystemManager().HandleAllSystems();

	glfwSwapBuffers(_window);

	assert(glGetError() == 0);
}