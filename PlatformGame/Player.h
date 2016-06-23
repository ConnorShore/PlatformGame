#pragma once

#include "Camera.h"
#include "InputManager.h"
#include "Agent.h"

class Player : public Agent
{
public:
	Player();
	~Player();

	void input(InputManager inputManager);
	void update() override;
	void render() override;

private:

};

