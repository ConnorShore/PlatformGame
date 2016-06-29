#include "AK47.h"
#include "ResourceManager.h"


AK47::AK47(const glm::vec2 & position, const glm::vec2 & dimension, const glm::vec2 & origin) : Weapon(position, dimension, origin, "Textures/ak47.png")
{
	_bulletDef.damage = 8.0f;
	_bulletDef.size = 1.0f;
	_bulletDef.speed = 10.0f;
	_bulletDef.position = position + glm::vec2(0.5f, -0.015f);
	_bulletDef.texture = ResourceManager::loadTexture("Textures/box.png");
}

AK47::AK47(const glm::vec2 & position, const glm::vec2 & origin) : Weapon(position, glm::vec2(1.2f, 0.55f), origin, "Textures/ak47.png")
{
	_bulletDef.damage = 8.0f;
	_bulletDef.size = 0.25f;
	_bulletDef.speed = 10.0f;
	_bulletDef.position = position + glm::vec2(0.5f, -0.015f);
	_bulletDef.texture = ResourceManager::loadTexture("Textures/box.png");
}

AK47::~AK47()
{
}
