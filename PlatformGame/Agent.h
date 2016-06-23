#pragma once

#include <GL\glew.h>
#include <Box2D\Box2D.h>
#include <string>

#include "Box.h"
#include "Texture.h"
#include "SpriteSheet.h"
#include "Vertex.h"

enum class AgentState {NONE, STANDING, WALKING, RUNNING, JUMPING, SHOOTING};

const int LEFT = -1;
const int RIGHT = 1;

class Agent
{
public:
	Agent();
	~Agent();

	void agentInit(b2World* world, const glm::vec2& position, const glm::vec2& dimension, const glm::vec2& drawDims, const glm::ivec2& sheetDims, const std::string& texPath);
	//void agentUpdate(); //< Update will go in here, but use this to determine collision/onground/etc stuff
	void agentRender();

	virtual void init() {}
	virtual void update() {}
	virtual void render() {}
	virtual glm::vec4 animate() { return glm::vec4(0, 0, 0, 0); }

	glm::vec2 getPosition() const { return glm::vec2(_body->GetPosition().x, _body->GetPosition().y); }
	glm::vec2 getDimension() const { return _dimension; }

protected:
	Texture _texture;
	SpriteSheet _spriteSheet;
	b2Body* _body = nullptr;
	b2Fixture* _fixture = nullptr;
	AgentState _agentState = AgentState::STANDING;

	glm::vec2 _dimension, _drawDims;
	float _animationTime = 0.0f;
	float _animationSpeed = 0.3f;
	int _direction = RIGHT;
	bool _onGround = false;	//< Add world collision (manifold) to determine

private:
	GLuint _vboID = 0;

	void initRender();
	void unbind();
};

