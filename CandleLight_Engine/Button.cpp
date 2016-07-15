#include "Button.h"

#include "ResourceManager.h"

Button::Button(GUI * prnt, glm::vec2 & position, glm::vec2 & dimension, const std::string & texPath, Color col) : GUI(prnt, position, dimension, ResourceManager::loadTexture(texPath), col)
{
	type = BUTTON;
}

Button::Button(glm::vec2 & position, glm::vec2 & dimension, const std::string& texPath, Color col) : GUI(position, dimension, ResourceManager::loadTexture(texPath), col)
{
	type = BUTTON;
}

Button::~Button()
{
}

void Button::onClick()
{
	if(eventCallback != NULL)
		eventCallback();
}