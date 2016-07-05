#pragma once

#include <glm\glm.hpp>
#include <Box2D\Box2D.h>

#include <CandleLight_Engine\Texture.h>

#include "Collision.h"

struct BulletDef
{
	glm::vec2 position, direction;
	float size, damage, speed;
	Texture texture;
	uint16 collisionCategory;
	uint16 collisionMask;
};