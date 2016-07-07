#pragma once

#include <glm\glm.hpp>
#include <CandleLight_Engine\SpriteBatch.h>
#include <CandleLight_Engine\Texture.h>
#include <CandleLight_Engine\SpriteSheet.h>

const float TILE_SIZE = 1.5f;

class Tile
{
public:
	Tile(const glm::vec2& pos, const int& index, Texture& tex);

	void render(SpriteBatch& spriteBatch);

private:
	glm::vec2 _position;
	glm::vec4 _uvRect;
	int _index;
	Texture _texture;
	SpriteSheet _spriteSheet;
};