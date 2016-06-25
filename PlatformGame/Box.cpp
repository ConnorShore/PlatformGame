#include "Box.h"


Box::Box()
{
	//Add support for rotation
}

Box::~Box()
{
}

void Box::init(b2World* world, const glm::vec2& position, const glm::vec2& dimension, const Texture& texture, float depth /*1.0f*/)
{
	_dimension = dimension;
	_texture = texture;
	_depth = depth;

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.fixedRotation = true;
	_body = world->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(_dimension.x / 2.0f, _dimension.y / 2.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.25f;
	_fixture = _body->CreateFixture(&fixtureDef);

	if (_vboID == 0)
		glGenBuffers(1, &_vboID);

	glm::vec4 destRect;
	destRect.x = _body->GetPosition().x - _dimension.x / 2.0f;
	destRect.y = _body->GetPosition().y - _dimension.y / 2.0f;
	destRect.z = _dimension.x;
	destRect.w = _dimension.y;
	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	Vertex vertexData[6];
	vertexData[0].setPosition(destRect.x, destRect.y + destRect.w);
	vertexData[0].setUV(uvRect.x, uvRect.y + uvRect.w);
	vertexData[1].setPosition(destRect.x, destRect.y);
	vertexData[1].setUV(uvRect.x, uvRect.y);
	vertexData[2].setPosition(destRect.x + destRect.z, destRect.y);
	vertexData[2].setUV(uvRect.x + uvRect.z, uvRect.y);

	//Second Triangle
	vertexData[3].setPosition(destRect.x + destRect.z, destRect.y);
	vertexData[3].setUV(uvRect.x + uvRect.z, uvRect.y);
	vertexData[4].setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
	vertexData[4].setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
	vertexData[5].setPosition(destRect.x, destRect.y + destRect.w);
	vertexData[5].setUV(uvRect.x, uvRect.y + uvRect.w);
}
void Box::render(SpriteBatch& spriteBatch)
{
	glm::vec4 destRect;
	destRect.x = _body->GetPosition().x - _dimension.x / 2.0f;
	destRect.y = _body->GetPosition().y - _dimension.y / 2.0f;
	destRect.z = _dimension.x;
	destRect.w = _dimension.y;
	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	spriteBatch.addToBatch(destRect, uvRect, Color(255, 255, 255, 255), _texture);
}
