#pragma once

#include <glm\glm.hpp>

#include "Texture.h"

class SpriteSheet
{
public:
	void init(Texture& tex, const glm::ivec2& uvDims)
	{
		sheet = tex;
		dims = uvDims;
	}


	glm::vec4 getUVs(int index)
	{
		int xTile = index % dims.x;
		int yTile = index / dims.x;

		glm::vec4 uvs;
		uvs.x = xTile / (float)dims.x;
		uvs.y = yTile / (float)dims.y;
		uvs.z = 1.0f / (float)dims.x;
		uvs.w = 1.0f / (float)dims.y;

		return uvs;
	}

	Texture sheet;
	glm::ivec2 dims;
};