#pragma once

#include "GUI.h"
#include "InputManager.h"
#include "Camera.h"

class Button : public GUI
{
public:
	Button(glm::vec2& position, glm::vec2& dimension, const std::string& texPath, Color col);
	~Button();

	//void update(InputManager& inputManager, Camera& camera);
	void onClick() override;

private:

};

