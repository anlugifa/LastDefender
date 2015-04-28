#include <conio.h>
#include <cstdio>
#include "Game.h"
#include "Console.h"
#include "InputControl.h"


InputControl::InputControl(IA *ia)
{
	_ia = ia;
}

bool InputControl::keydown(int key)
{
	return (GetAsyncKeyState(key) && 0x8000) != 0;
}

bool InputControl::processInput()
{
	if (keydown(VK_ESCAPE))
	{
		return false;
	}

	if (keydown(VK_SPACE))
	{
		_ia->keySpaceEvent();
	}
		
	if (!_ia->getProtector()->canMove())
		return true;

	if (keydown(VK_LEFT) || keydown(VK_NUMPAD4) || keydown(0x41))
	{
		_ia->keyLeftEvent();
	}
	if (keydown(VK_RIGHT) || keydown(VK_NUMPAD6) || keydown(0x44))
	{
		_ia->keyRightEvent();
	}
	if (keydown(VK_UP) || keydown(VK_NUMPAD8) || keydown(0x57))
	{
		_ia->keyUpEvent();
	}
	if (keydown(VK_DOWN) || keydown(VK_NUMPAD2) || keydown(0x53))
	{
		_ia->keyDownEvent();
	}
	

	return true;
}