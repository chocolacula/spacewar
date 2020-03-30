#include "Engine.h"

#include <GL/gl.h>
#include <cassert>
#include <windowsx.h>

#include "Scene.h"
#include "Types/Color.h"

#include "Input.h"
#include "ECS/System/SystemManager.h"
#include "Types/Vector2.h"

int	Engine::_windowWidth = 0;
int	Engine::_windowHeight = 0;
int	Engine::_maxFPS = 60;

HDC	  Engine::_windowDC = nullptr;
HGLRC Engine::_openGLHandle = nullptr;

LARGE_INTEGER Engine::_clockFrequency;
LARGE_INTEGER Engine::_clockLastTick;

float Engine::_deltaTime = 0;

HWND Engine::_windowHandle = nullptr;

void Engine::Run(const char* name, int windowWidth, int windowHeight)
{
	Init(name, windowWidth, windowHeight);

	// The main engine loop
	while (true)
	{
		MSG msg;
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		NextFrame();
		Input::NextFrame();
	}

	ResetOpenGL();
	DestroyWindow(_windowHandle);
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
	InitOpenGL();

	QueryPerformanceFrequency(&_clockFrequency);
	QueryPerformanceCounter(&_clockLastTick);
}

void Engine::InitWindow(const char* name, int windowWidth, int windowHeight)
{
	WNDCLASSEX windowClass;

	windowClass.cbSize = sizeof(windowClass);
	windowClass.hInstance = GetModuleHandle(nullptr);
	windowClass.lpszClassName = name;
	windowClass.lpfnWndProc = WindowProc;
	windowClass.style = CS_DBLCLKS;

	windowClass.hIcon = nullptr;
	windowClass.hIconSm = nullptr;

	windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);

	windowClass.lpszMenuName = nullptr;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hbrBackground = nullptr;

	RegisterClassEx(&windowClass);

	RECT windowRect;
	windowRect.left = windowRect.top = 0;
	windowRect.bottom = windowHeight;
	windowRect.right = windowWidth;
	AdjustWindowRect(&windowRect, WS_CAPTION | WS_SYSMENU, FALSE);

	const auto screenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
	const auto screenHeight = GetSystemMetrics(SM_CYFULLSCREEN);

	_windowHandle = CreateWindowEx(0, windowClass.lpszClassName, name, WS_CAPTION | WS_SYSMENU,
		screenWidth / 2 - windowWidth / 2, screenHeight / 2 - windowHeight / 2,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		HWND_DESKTOP, nullptr, GetModuleHandle(nullptr), nullptr);

	ShowWindow(_windowHandle, SW_SHOW);
}

LRESULT CALLBACK Engine::WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		case WM_KEYDOWN:
			Input::SetKeyDown(wParam);
			break;

		case WM_KEYUP:
			Input::SetKeyUp(wParam);
			break;

		case WM_MOUSEMOVE:
			{
				const auto screenX = (float)GET_X_LPARAM(lParam) / _windowWidth;
				const auto screenY = (float)GET_Y_LPARAM(lParam) / _windowHeight;

				Input::SetMousePosition({ screenX * Scene::scale.x * 2 - Scene::scale.x,
										-(screenY * Scene::scale.y * 2 - Scene::scale.y) });
			}
			break;

		case WM_LBUTTONDOWN:
			Input::SetMouseButtonNumber(0);
			break;
		
		case WM_RBUTTONDOWN:
			Input::SetMouseButtonNumber(1);
			break;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}

void Engine::InitOpenGL()
{
	_windowDC = GetDC(_windowHandle);

	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(pfd));
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.iLayerType = PFD_MAIN_PLANE;
	int npfd = ChoosePixelFormat(_windowDC, &pfd);

	memset(&pfd, 0, sizeof(pfd));
	pfd.nSize = sizeof(pfd);
	SetPixelFormat(_windowDC, npfd, &pfd);

	_openGLHandle = wglCreateContext(_windowDC);
	wglMakeCurrent(_windowDC, _openGLHandle);

	glClearColor(Scene::clearColor.red, Scene::clearColor.green, Scene::clearColor.blue, Scene::clearColor.alpha);

	// font render support
	HFONT font = CreateFont(40, 0, 0, 0,
		FW_NORMAL, FALSE, FALSE, FALSE,
		ANSI_CHARSET, 0,
		0, 0, 0, "Unispace");
	
	SelectObject(_windowDC, font);
	wglUseFontBitmaps(_windowDC, 0, 255, 1000);
	glListBase(1000);
}

void Engine::ResetOpenGL()
{
	wglMakeCurrent(nullptr, nullptr);
	wglDeleteContext(_openGLHandle);
	ReleaseDC(_windowHandle, _windowDC);
	_openGLHandle = nullptr;
	_windowDC = nullptr;
}

void Engine::NextFrame()
{
	_deltaTime = 0;

	while (true)
	{
		LARGE_INTEGER clockTick;
		QueryPerformanceCounter(&clockTick);
		
		const double deltaTime = (double)(clockTick.QuadPart - _clockLastTick.QuadPart) / (double)_clockFrequency.QuadPart;
		if (deltaTime >= 1.0 / _maxFPS)
		{
			_deltaTime = (float)deltaTime;
			_clockLastTick = clockTick;
			break;
		}
	}

	// Reset render data
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glScalef(1 / Scene::scale.x, 1 / Scene::scale.y, 0.f);

	glDisable(GL_CULL_FACE);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	// Handle all systems
	Scene::GetSystemManager().HandleAllSystems();

	SwapBuffers(_windowDC);
	assert(glGetError() == 0);
}