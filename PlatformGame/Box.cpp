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
	bodyDef.fixedRotation = false;
	_body = world->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(_dimension.x / 2.0f, _dimension.y / 2.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.25f;
	_fixture = _body->CreateFixture(&fixtureDef);
}

void Box::render(SpriteBatch& spriteBatch)
{
	glm::vec4 destRect;
	destRect.x = _body->GetPosition().x - _dimension.x / 2.0f;
	destRect.y = _body->GetPosition().y - _dimension.y / 2.0f;
	destRect.z = _dimension.x;
	destRect.w = _dimension.y;
	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	spriteBatch.addToBatch(destRect, uvRect, 1.0f, _texture.id, Color(255, 255, 255, 255), _body->GetAngle(), false);
}
