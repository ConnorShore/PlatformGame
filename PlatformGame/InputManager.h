#pragma once

#include <unordered_map>

class InputManager
{
public:
	InputManager();
	~InputManager();

	void update();
	
	void keyPressed(unsigned int key);
	void keyReleased(unsigned int key);
	bool isKeyDown(unsigned int key);

private:
	std::unordered_map<unsigned int, bool> _keyMap;
};
