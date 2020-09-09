#include <iostream>
#include <Scene.h>
#include <Engine.h>
#include "Input.h"
#include "Types/Vector2.h"

Keyboard Input::_activeKeyDown = Keyboard::None;
Keyboard Input::_activeKeyUp   = Keyboard::None;

Mouse Input::_activeMouseButtonDown = Mouse::None;
Mouse Input::_activeMouseButtonUp   = Mouse::None;

Vector2 Input::_mousePosition = Vector2::ZERO;

Keyboard Input::GetKeyDown()
{
	return _activeKeyDown;
}

Keyboard Input::GetKeyUp()
{
	return _activeKeyUp;
}

Mouse Input::GetMouseButtonDown()
{
	return _activeMouseButtonDown;
}

Mouse Input::GetMouseButtonUp()
{
    return _activeMouseButtonUp;
}

Vector2 Input::GetMousePosition()
{
	return _mousePosition;
}

void Input::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS || action == GLFW_REPEAT)
        _activeKeyDown = static_cast<Keyboard>(key);
    else if (action == GLFW_RELEASE)
        _activeKeyUp = static_cast<Keyboard>(key);
}

void Input::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (action == GLFW_PRESS || action == GLFW_REPEAT)
        _activeMouseButtonDown = static_cast<Mouse>(button);
    else if (action == GLFW_RELEASE)
        _activeMouseButtonUp = static_cast<Mouse>(button);
}

// Can't set _activeMouseButtonUp it's a scroll and there is nothing to Up
void Input::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (yoffset < 0)
        _activeMouseButtonDown = Mouse::WheelDown;
    else if (yoffset > 0)
        _activeMouseButtonDown = Mouse::WheelUp;
}

void Input::cursor_position_callback(GLFWwindow* window, double x, double y)
{
	float screenX = x / Engine::GetWindowWidth();
	float screenY = y / Engine::GetWindowHeight();

	_mousePosition = Vector2({ screenX * Scene::scale.x * 2 - Scene::scale.x,
							 -(screenY * Scene::scale.y * 2 - Scene::scale.y) });
}

void Input::Reset()
{
    _activeKeyDown = Keyboard::None;
    _activeKeyUp   = Keyboard::None;

    _activeMouseButtonDown = Mouse::None;
    _activeMouseButtonUp   = Mouse::None;
}
