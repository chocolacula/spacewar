#pragma once

#include <wtypes.h>

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

	static HDC _windowDC;
	static HGLRC _openGLHandle;

	static LARGE_INTEGER _clockFrequency;
	static LARGE_INTEGER _clockLastTick;

	static float _deltaTime;

	static void Init(const char* name, int windowWidth, int windowHeight);
	static void InitWindow(const char* name, int windowWidth, int windowHeight);
	
	static void InitOpenGL();
	static void ResetOpenGL();

	static void NextFrame();

	static HWND _windowHandle;
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
};