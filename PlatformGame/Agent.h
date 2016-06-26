#pragma once

#include <GL\glew.h>
#include <Box2D\Box2D.h>
#include <string>
#include <vector>

#include "Texture.h"
#include "SpriteSheet.h"
#include "Vertex.h"
#include "SpriteBatch.h"
#include "Weapon.h"

class Weapon;

enum class AgentState {NONE, STANDING, WALKING, RUNNING, JUMPING, SHOOTING};

const int LEFT = -1;
const int RIGHT = 1;

class Agent
{
public:
	Agent();
	~Agent();

	void agentInit(b2World* world, const glm::vec2& position, const glm::vec2& dimension, const glm::ivec2& sheetDims, const std::string& texPath);
	void agentUpdate(); //< Update will go in here, but use this to determine collision/onground/etc stuff
	void agentRender(SpriteBatch& spriteBatch);

	void addWeapon(Weapon* weapon);

	virtual void init() {}
	virtual void update() {}
	virtual void render() {}
	virtual glm::vec4 animate() { printf("Agent\n"); return glm::vec4(0, 0, 0, 0); };

	glm::vec2 getPosition() const { return glm::vec2(_body->GetPosition().x, _body->GetPosition().y); }
	glm::vec2 getDimension() const { return _dimension; }

	int getDirection() const { return _direction; }

protected:
	Texture _texture;
	SpriteSheet _spritesheet;
	b2Body* _body = nullptr;
	b2Fixture* _fixture = nullptr;
	AgentState _agentState = AgentState::STANDING;

	glm::vec2 _dimension;
	glm::vec4 _uvRect;
	float _animationTime = 0.0f;
	float _animationSpeed = 0.3f;
	int _direction = RIGHT;
	bool _onGround = false;	//< Add world collision (manifold) to determine
	bool _canJump = false;

	std::vector<Weapon*> _weapons;

	void jump();
};

