#include "Button.h"

#include "ResourceManager.h"

Button::Button(glm::vec2 & position, glm::vec2 & dimension, const std::string& texPath, Color col) : GUI(position, dimension, ResourceManager::loadTexture(texPath), col)
{
}

Button::~Button()
{
}
//
//void Button::update(InputManager& inputManager, Camera& camera)
//{
//	if (inBox(camera.screenToWorldCoords(inputManager.getMousePos()))) {
//		if()
//	}
//}

void Button::onClick()
{
	printf("working\n");
}