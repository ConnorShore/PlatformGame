#pragma once

#include "Camera.h"
#include "InputManager.h"
#include "Agent.h"

class Player : public Agent
{
public:
	Player();
	~Player();

	void input(InputManager inputManager, Camera& camera);
	void init() override;
	void update() override;
	void render() override;
	glm::vec4 animate() override;

private:
	const float MAX_SPEED = 6.0f;
};

