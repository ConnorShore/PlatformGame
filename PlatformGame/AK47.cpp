#include "AK47.h"
#include <CandleLight_Engine\ResourceManager.h>


AK47::AK47(const glm::vec2 & position, const glm::vec2 & dimension, const glm::vec2 & origin) : Weapon(position, dimension, origin, "Textures/ak47.png")
{
	initStats(position);
}

AK47::AK47(const glm::vec2 & position, const glm::vec2 & origin) : Weapon(position, glm::vec2(1.2f, 0.55f), origin, "Textures/ak47.png")
{
	initStats(position);
}

AK47::~AK47()
{

}

void AK47::initStats(const glm::vec2& position)
{
	_name = "ak47";
	_bulletDef.damage = 8.0f;
	_bulletDef.size = 0.25f;
	_bulletDef.speed = 40.0f;
	_bulletDef.position = position + glm::vec2(0.5f, -0.015f);
	_bulletDef.texture = ResourceManager::loadTexture("Textures/boxTex.png");

	_fireRate = 7.5f;
}
