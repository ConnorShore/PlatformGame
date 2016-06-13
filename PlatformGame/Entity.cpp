#include "Entity.h"


Entity::Entity()
{
}

Entity::~Entity()
{
}

void Entity::init(b2World* world, const glm::vec2& position, const glm::vec2& dimension, const Texture& texture, float depth /*1.0f*/)
{
	_dimension = dimension;
	_texture = texture;
	_depth = depth;

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	_body = world->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(dimension.x, dimension.y);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.25f;

	_fixture = _body->CreateFixture(&fixtureDef);
;
	if (_vboID == 0)
		glGenBuffers(1, &_vboID);

	Vertex vertexData[6];
	vertexData[0].setPosition(_body->GetPosition().x+ _dimension.x, _body->GetPosition().y + _dimension.y);
	vertexData[0].setUV(1.0f, 1.0f);
	vertexData[1].setPosition(_body->GetPosition().x, _body->GetPosition().y + _dimension.y);
	vertexData[1].setUV(0.0f, 1.0f);
	vertexData[2].setPosition(_body->GetPosition().x, _body->GetPosition().y);
	vertexData[2].setUV(0.0f, 0.0f);

	//Second Triangle
	vertexData[3].setPosition(_body->GetPosition().x, _body->GetPosition().y);
	vertexData[3].setUV(0.0f, 0.0f);
	vertexData[4].setPosition(_body->GetPosition().x+ _dimension.x, _body->GetPosition().y);
	vertexData[4].setUV(1.0f, 0.0f);
	vertexData[5].setPosition(_body->GetPosition().x+ _dimension.x, _body->GetPosition().y + _dimension.y);
	vertexData[5].setUV(1.0f, 1.0f);

	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//setupSprite(_body->GetPosition().x, _body->GetPosition().y, _dimension.x, _dimension.y);
	//setupBox2D(world, glm::vec4(_position, _dimension));
}

void Entity::update()
{
}

void Entity::render()
{
	Vertex vertexData[6];
	vertexData[0].setPosition(_body->GetPosition().x + _dimension.x, _body->GetPosition().y + _dimension.y);
	vertexData[0].setUV(1.0f, 1.0f);
	vertexData[1].setPosition(_body->GetPosition().x, _body->GetPosition().y + _dimension.y);
	vertexData[1].setUV(0.0f, 1.0f);
	vertexData[2].setPosition(_body->GetPosition().x, _body->GetPosition().y);
	vertexData[2].setUV(0.0f, 0.0f);

	//Second Triangle
	vertexData[3].setPosition(_body->GetPosition().x, _body->GetPosition().y);
	vertexData[3].setUV(0.0f, 0.0f);
	vertexData[4].setPosition(_body->GetPosition().x + _dimension.x, _body->GetPosition().y);
	vertexData[4].setUV(1.0f, 0.0f);
	vertexData[5].setPosition(_body->GetPosition().x + _dimension.x, _body->GetPosition().y + _dimension.y);
	vertexData[5].setUV(1.0f, 1.0f);

	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	//glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _texture.id);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
//
//void Entity::setupSprite(float& x, float& y, float& _dimension.x, float& _dimension.y)
//{
//	if (_vaoID == 0)
//		glGenVertexArrays(1, &_vaoID);
//	if (_vboID == 0)
//		glGenBuffers(1, &_vboID);
//
//	Verte_body->GetPosition().xvertexData[6];
//	vertexData[0].setPosition(_body->GetPosition().x+ _dimension.x, _body->GetPosition().y + _dimension.y);
//	vertexData[0].setUV(1.0f, 1.0f);
//	vertexData[1].setPosition(x, _body->GetPosition().y + _dimension.y);
//	vertexData[1].setUV(0.0f, 1.0f);
//	vertexData[2].setPosition(x, y);
//	vertexData[2].setUV(0.0f, 0.0f);
//
//	//Second Triangle
//	vertexData[3].setPosition(x, y);
//	vertexData[3].setUV(0.0f, 0.0f);
//	vertexData[4].setPosition(_body->GetPosition().x+ _dimension.x, y);
//	vertexData[4].setUV(1.0f, 0.0f);
//	vertexData[5].setPosition(_body->GetPosition().x+ _dimension.x, _body->GetPosition().y + _dimension.y);
//	vertexData[5].setUV(1.0f, 1.0f);
//
//	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//}
//
//void Entity::setupBox2D(b2World* world, const glm::vec4& destRect)
//{
//	b2BodyDef bodyDef;
//	bodyDef.type = b2_dynamicBody;
//	bodyDef.position.Set(destRect.x, destRect.y);
//	_bod_body->GetPosition().y = world->CreateBody(&bodyDef);
//	
//	b2PolygonShape dynamicBox;
//	dynamicBox.SetAsBox(destRect.z, destRect.w);
//
//	b2FixtureDef fixtureDef;
//	fixtureDef.shape = &dynamicBox;
//	fixtureDef.densit_body->GetPosition().y = 1.0f;
//	fixtureDef.friction = 0.25f;
//
//	_body->CreateFixture(&fixtureDef);
//}
