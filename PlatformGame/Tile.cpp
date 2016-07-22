#include "Tile.h"

Tile::Tile(const glm::vec2 & pos, const int& index, Texture& tex) : _position(pos), _index(index), _texture(tex)
{
	_spriteSheet.init(_texture, glm::ivec2(8, 8));
}

void Tile::render(SpriteBatch & spriteBatch)
{
	glm::vec4 destRect(_position.x, _position.y, TILE_SIZE, TILE_SIZE);
	_uvRect = _spriteSheet.getUVs(_index);
	spriteBatch.addToBatch(destRect, _uvRect, 1.0f, _texture.id, Color(255, 255, 255, 255));
}
