#pragma once

#include <cstdint>
#include <GLFW/glfw3.h>
#include "Keyboard.h"
#include "Mouse.h"

struct Vector2;

class Input
{
public:
	Input() = delete;

	static Keyboard GetKeyDown();
	static Keyboard GetKeyUp();
	static Mouse    GetMouseButtonDown();
    static Mouse    GetMouseButtonUp();
	static Vector2  GetMousePosition();

private:
	static Keyboard _activeKeyDown;
	static Keyboard _activeKeyUp;
	
	static Mouse _activeMouseButtonDown;
    static Mouse _activeMouseButtonUp;

	static Vector2 _mousePosition;

    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    static void cursor_position_callback(GLFWwindow* window, double x, double y);

	static void Reset();

	friend class Engine;
};