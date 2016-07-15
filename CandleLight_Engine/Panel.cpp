#include "Panel.h"

#include "ResourceManager.h"

Panel::Panel(GUI * prnt, glm::vec2 & position, glm::vec2 & dimension, const std::string & texPath, Color col) : GUI(prnt, position, dimension, ResourceManager::loadTexture(texPath), col)
{
	type = PANEL;
}

Panel::Panel(glm::vec2 & position, glm::vec2 & dimension, const std::string & texPath, Color col) : GUI(position, dimension, ResourceManager::loadTexture(texPath), col)
{
	type = PANEL;
}

Panel::~Panel()
{
}
