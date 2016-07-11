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

bool Button::inBox(const glm::vec2& pos)
{
	return (pos.x > position.x && pos.y > position.y && pos.x < (position.x + dimension.x) && pos.y < (position.y + dimension.y));
}

void Button::onClick()
{
	
}