#pragma once

#include <CandleLight_Engine\InputManager.h>
#include <CandleLight_Engine\Camera.h>

#include "Human.h"

class Player : public Human
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

