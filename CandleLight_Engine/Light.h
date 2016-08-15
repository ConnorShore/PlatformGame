#pragma once

#include <glm\glm.hpp>

#include "Vertex.h"
#include "SpriteBatch.h"
#include "Texture.h"

struct Light
{
	void render(SpriteBatch& spriteBatch)
	{
		glm::vec4 destRect(position.x - size / 2.0f, position.y - size / 2.0f, size, size);
		spriteBatch.addToBatch(destRect, glm::vec4(0,0,1,1), 0.0f, texture.id, color);
	}

	glm::vec2 position;
	float size;
	Color color;
	Texture texture;
};