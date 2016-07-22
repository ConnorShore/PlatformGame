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

void Button::update()
{
	if (_enabled) {
		if (mouseOver) {
			color.a = 255;
		}
		else {
			color.a = 200;
		}
	}
	else {
		color = Color(100, 100, 100, 100);
	}
}

void Button::onClick()
{
	if (_enabled) {
		if (eventCallback != NULL)
			eventCallback();
	}
}