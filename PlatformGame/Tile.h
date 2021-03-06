#pragma once

#include <glm\glm.hpp>
#include <CandleLight_Engine\SpriteBatch.h>
#include <CandleLight_Engine\Texture.h>
#include <CandleLight_Engine\SpriteSheet.h>

const float TILE_SIZE = 1.0f;

class Tile
{
public:
	Tile(const glm::vec2& pos, const int& index, Texture& tex);

	void render(SpriteBatch& spriteBatch);

	glm::vec2 getPosition() const { return _position; }
	int getIndex() const { return _index; }

private:
	glm::vec2 _position;
	glm::vec4 _uvRect;
	int _index;
	Texture _texture;
	SpriteSheet _spriteSheet;
};