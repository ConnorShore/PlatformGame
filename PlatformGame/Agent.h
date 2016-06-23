#pragma once

#include <GL\glew.h>
#include <Box2D\Box2D.h>
#include <string>

#include "Box.h"
#include "Texture.h"
#include "SpriteSheet.h"
#include "Vertex.h"

enum class AgentState {NONE, WALKING, RUNNING, JUMPING, SHOOTING};

const int LEFT = -1;
const int RIGHT = 1;

class Agent
{
public:
	Agent();
	~Agent();

	void init(b2World* world, const glm::vec2& position, const glm::vec2& dimension, const glm::ivec2& sheetDims, const std::string& texPath);
	void agentRender();

	virtual void update() {}
	virtual void render() {}

	glm::vec2 getPosition() const { return glm::vec2(_body->GetPosition().x, _body->GetPosition().y); }

protected:
	Texture _texture;
	SpriteSheet _spriteSheet;
	b2Body* _body = nullptr;
	b2Fixture* _fixture = nullptr;
	glm::vec2 _dimension;
	int _direction = RIGHT;

private:
	GLuint _vboID = 0;
};

