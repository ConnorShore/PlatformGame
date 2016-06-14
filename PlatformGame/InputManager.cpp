#include "InputManager.h"

#include <SDL\SDL.h>


InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

void InputManager::update()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_QUIT:
			//Send message to maingame to exit
			exit(0);
			break;
		case SDL_KEYDOWN:
			keyPressed(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			keyReleased(evnt.key.keysym.sym);
			break;
		}
	}
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
