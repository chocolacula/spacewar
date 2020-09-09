#pragma once

#include <GLFW/glfw3.h>

class Engine
{
public:
	static void Run(const char* name, int windowWidth, int windowHeight);

	static int GetWindowWidth();
	static int GetWindowHeight();

	static int SetMaxFPS(int maxFPS);

	static float DeltaTime();

private:
	static int _windowWidth;
	static int _windowHeight;
	static int _maxFPS;

//	static HDC _windowDC;
//	static HGLRC _openGLHandle;

	static float  _deltaTime;
	static double _lastTime;

	static void Init(const char* name, int windowWidth, int windowHeight);
	static void InitWindow(const char* name, int windowWidth, int windowHeight);
	
	static void InitOpenGL();
//	static void ResetOpenGL();

    static void MainLoop();
	static void RenderNextFrame();

    static GLFWwindow* _window;
};