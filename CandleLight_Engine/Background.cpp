#include "Background.h"
#include "ResourceManager.h"


Background::Background()
{
}


Background::~Background()
{
}

void Background::init(const std::string & filePath, const glm::vec2& position, const glm::vec2& dimension, int depth, int numRepeats)
{
	_texture = ResourceManager::loadTexture(filePath);
	_position = position;
	_offset = position;
	_dimension = glm::vec2(dimension.x * numRepeats, dimension.y);
	_depth = depth;
	_numRepeats = numRepeats;
}

void Background::update(const glm::vec2& position)
{
	switch (_depth) {
	case 0:
		_position.x = (position.x * 0.9f) + _offset.x;
		_position.y = position.y + _offset.y / 1.75f;
		break;
	case 1:
		_position.x = (position.x * 0.7f) + _offset.x;
		_position.y = (position.y * 0.5f) + _offset.y / 1.15f;
		break;
	case 2:
		_position.x = (position.x * 0.4f) + _offset.x;
		_position.y = (position.y * 0.22f) + _offset.y;
		break;
	default:
		printf("%f is not a valid background depth", _depth);
		break;
	}
}

void Background::render(SpriteBatch & spriteBatch)
{
	spriteBatch.addToBatch(glm::vec4(_position.x, _position.y, _dimension.x, _dimension.y),
		glm::vec4(0.0f, 0.0f, (float)_numRepeats, 1.0f), (float)_depth, _texture.id, Color(255, 255, 255, 255));
}
