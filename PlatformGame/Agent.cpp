#include "Agent.h"
#include "ResourceManager.h"

#include <iostream>

Agent::Agent()
{
}


Agent::~Agent()
{
}

void Agent::agentInit(b2World* world, const glm::vec2& position, const glm::vec2& dimension, const glm::ivec2& sheetDims, const std::string& texPath)
{
	_texture = ResourceManager::loadTexture(texPath);
	_dimension = dimension;

	_spritesheet.init(_texture, sheetDims);
	
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.fixedRotation = true;
	_body = world->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(dimension.x / 2.0f, dimension.y / 2.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.25f;
	_fixture = _body->CreateFixture(&fixtureDef);

	init();
}

void Agent::agentRender(SpriteBatch& spriteBatch)
{
	glm::vec4 destRect;
	destRect.x = _body->GetPosition().x - _dimension.x / 2.0f;
	destRect.y = _body->GetPosition().y - _dimension.y / 2.0f;
	destRect.z = _dimension.x;
	destRect.w = _dimension.y;
	glm::vec4 uvRect = animate();

	spriteBatch.addToBatch(destRect, uvRect, 1.0f, _texture.id, Color(255, 255, 255, 255));

	render();
}

void Agent::jump()
{
}
