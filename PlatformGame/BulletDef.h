#pragma once

#include "Texture.h"

#include <glm\glm.hpp>

struct BulletDef
{
	glm::vec2 position, direction;
	float size, damage, speed;
	Texture texture;
};