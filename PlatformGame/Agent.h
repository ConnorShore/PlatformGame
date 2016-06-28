#pragma once

#include <GL\glew.h>
#include <Box2D\Box2D.h>
#include <string>

#include "Texture.h"
#include "SpriteSheet.h"
#include "Vertex.h"
#include "SpriteBatch.h"

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

	int getDirection() const { return _direction; }

protected:
	Texture _texture;
	SpriteSheet _spritesheet;
	b2Body* _body = nullptr;
	b2Fixture* _fixture = nullptr;
	AgentState _agentState = AgentState::STANDING;
	int _direction = RIGHT;

	glm::vec2 _dimension;
	glm::vec4 _uvRect;

	float _animationTime = 0.0f;
	float _animationSpeed = 0.3f;
};

