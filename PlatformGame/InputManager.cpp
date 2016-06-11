#include "InputManager.h"

#include <SDL\SDL.h>


InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

void InputManager::keyPressed(unsigned int key)
{
	_keyMap[key] = true;
}

void InputManager::keyReleased(unsigned int key)
{
	_keyMap[key] = false;
}

bool InputManager::isKeyDown(unsigned int key)
{
	auto it = _keyMap.find(key);
	if (it != _keyMap.end())
		return it->second;
	else
		return false;
}
