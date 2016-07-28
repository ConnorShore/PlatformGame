#pragma once

#include <GL\glew.h>
#include <Box2D\Box2D.h>
#include <string>

#include <CandleLight_Engine\Texture.h>
#include <CandleLight_Engine\SpriteSheet.h>
#include <CandleLight_Engine\Vertex.h>
#include <CandleLight_Engine\SpriteBatch.h>

#include "Collision.h"

enum class AgentState { NONE, STANDING, WALKING, RUNNING, JUMPING, SHOOTING };

const int LEFT = -1;
const int RIGHT = 1;

class Agent
{
public:
	Agent();
	~Agent();

	virtual void init() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
	virtual glm::vec4 animate() = 0;

	glm::vec2 getPosition() const { return glm::vec2(_body->GetPosition().x, _body->GetPosition().y); }
	glm::vec2 getDimension() const { return _dimension; }
	Texture getTexture() const { return _texture; }

	int getDirection() const { return _direction; }

	uint16 getCollisionCategory() { return _collisionCategory; }
	uint16 getCollisionMask() { return _collisionMask; }

	void setPosition(const glm::vec2& pos) {  }

protected:
	Texture _texture;
	SpriteSheet _spritesheet;
	b2Body* _body = nullptr;
	b2Fixture* _fixture = nullptr;
	AgentState _agentState = AgentState::STANDING;

	uint16 _collisionCategory = CATEGORY_NEUTRAL;
	uint16 _collisionMask = MASK_ALL;

	int _direction = RIGHT;

	glm::vec2 _dimension;
	glm::vec4 _uvRect;

	float _animationTime = 0.0f;
	float _animationSpeed = 0.3f;
};

