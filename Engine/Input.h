#pragma once

#include <wtypes.h>
#include <cstdint>

struct Vector2;

class Input
{
public:
	Input() = delete;
	
	enum class Keys : uint64_t
	{
		None = 0,
		W = 'W',
		A = 'A',
		D = 'D',
		Space = 0x20
	};

	static Keys GetKeyDown();
	static Keys GetKeyUp();
	static bool GetMouseButtonDown(int buttonNumber);
	static Vector2 GetMousePosition();

private:
	static Keys _activeKeyDown;
	static Keys _activeKeyUp;
	
	static int _mouseButtonNumber;
	static Vector2 _mousePosition;

	static void SetKeyDown(WPARAM key);
	static void SetKeyUp(WPARAM key);
	static void SetMouseButtonNumber(int buttonNumber);
	static void SetMousePosition(Vector2 position);

	static void NextFrame();

	friend class Engine;
};