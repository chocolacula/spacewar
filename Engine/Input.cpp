#include "Input.h"
#include "Types/Vector2.h"

Input::Keys Input::_activeKeyDown = Keys::None;
Input::Keys Input::_activeKeyUp   = Keys::None;
int Input::_mouseButtonNumber = -1;
Vector2 Input::_mousePosition = Vector2::ZERO;

Input::Keys Input::GetKeyDown()
{
	return _activeKeyDown;
}

Input::Keys Input::GetKeyUp()
{
	return _activeKeyUp;
}

bool Input::GetMouseButtonDown(int buttonNumber)
{
	return _mouseButtonNumber == buttonNumber;
}

Vector2 Input::GetMousePosition()
{
	return _mousePosition;
}

void Input::SetKeyDown(WPARAM key)
{
	_activeKeyDown = static_cast<Keys>(key);
}

void Input::SetKeyUp(WPARAM key)
{
	_activeKeyUp = static_cast<Keys>(key);
}

void Input::SetMouseButtonNumber(int buttonNumber)
{
	_mouseButtonNumber = buttonNumber;
}

void Input::SetMousePosition(Vector2 position)
{
	_mousePosition = position;
}

void Input::NextFrame()
{
	_activeKeyDown = Keys::None;
	_activeKeyUp   = Keys::None;
	_mouseButtonNumber = -1;
}
