#include "Icon.h"
#include "ResourceManager.h"


Icon::Icon(GUI * prnt, glm::vec2 & position, float size, const std::string & texPath, Color col) : GUI(prnt, position, glm::vec2(size), ResourceManager::loadTexture(texPath), col)
{
	type = ICON;
}

Icon::Icon(glm::vec2 & position, float size, const std::string & texPath, Color col) : GUI(position, glm::vec2(size), ResourceManager::loadTexture(texPath), col)
{
	type = ICON;
}

Icon::Icon(const std::string & texPath) : GUI(glm::vec2(1.0f), glm::vec2(1.0f), ResourceManager::loadTexture(texPath), Color(255, 255, 255, 255))
{
	type = ICON;
}

Icon::~Icon()
{
}
