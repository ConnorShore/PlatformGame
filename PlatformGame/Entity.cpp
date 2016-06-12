#include "Entity.h"


Entity::Entity()
{
}

Entity::~Entity()
{
}

void Entity::init(const glm::vec2& position, const glm::vec2& dimension, const Texture& texture, float depth /*1.0f*/)
{
	_position = position;
	_dimension = dimension;
	_texture = texture;
	_depth = depth;

	//setupSprite(_position.x, _position.y, _dimension.x, _dimension.y);
}

void Entity::update(float delta)
{
}

void Entity::render()
{
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _texture.id);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

	glDrawArrays(GL_TRIANGLES, 0, 6);

}

void Entity::setupSprite(float x, float y, float width, float height)
{
	if (_vaoID == 0)
		glGenVertexArrays(1, &_vaoID);
	if (_vboID == 0)
		glGenBuffers(1, &_vboID);

	Vertex vertexData[6];
	vertexData[0].setPosition(x + width, y + height);
	vertexData[0].setUV(1.0f, 1.0f);
	vertexData[1].setPosition(x, y + height);
	vertexData[1].setUV(0.0f, 1.0f);
	vertexData[2].setPosition(x, y);
	vertexData[2].setUV(0.0f, 0.0f);

	//Second Triangle
	vertexData[3].setPosition(x, y);
	vertexData[3].setUV(0.0f, 0.0f);
	vertexData[4].setPosition(x + width, y);
	vertexData[4].setUV(1.0f, 0.0f);
	vertexData[5].setPosition(x + width, y + height);
	vertexData[5].setUV(1.0f, 1.0f);

	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
