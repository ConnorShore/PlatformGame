#include "Player.h"

#include <SDL\SDL_keyboard.h>

Player::Player()
{
}


Player::~Player()
{
}

void Player::init()
{
	
}

void Player::update()
{
	
}

void Player::input(InputManager inputManager)
{
	if (inputManager.isKeyDown(SDLK_d)) {
		_body->ApplyForceToCenter(b2Vec2(100.0f, 0.0f));
		_agentState = AgentState::RUNNING;
		_direction = RIGHT; //< Make direction based on mouse position
	}
	else if (inputManager.isKeyDown(SDLK_a)) {
		_body->ApplyForceToCenter(b2Vec2(-100.0f, 0.0f));
		_agentState = AgentState::RUNNING;
		_direction = LEFT;
	}
	else {
		_body->SetLinearVelocity(b2Vec2(_body->GetLinearVelocity().x * 0.7f, _body->GetLinearVelocity().y));
	}

	if (inputManager.isKeyDown(SDLK_w)) {
		_body->ApplyForceToCenter(b2Vec2(0.0f, 150.0f));
	}

	if (_body->GetLinearVelocity().x > MAX_SPEED) {
		_body->SetLinearVelocity(b2Vec2(MAX_SPEED, _body->GetLinearVelocity().y));
	}
	if (_body->GetLinearVelocity().x < -MAX_SPEED) {
		_body->SetLinearVelocity(b2Vec2(-MAX_SPEED, _body->GetLinearVelocity().y));
	}
}

void Player::render()
{
	
}

glm::vec4 Player::animate()
{
	glm::vec2 velocity = glm::vec2(_body->GetLinearVelocity().x, _body->GetLinearVelocity().y);
	int tileIndex, numTiles;

	//Running
	if (glm::abs(velocity.x) > 1.0f) {
		tileIndex = 0;
		numTiles = 10;
		_animationSpeed = glm::abs(velocity.x) * 0.04f;

		if (_agentState != AgentState::RUNNING) {
			_agentState = AgentState::RUNNING;
			_animationTime = 0.0f;
		}
	}
	//Standing
	else {
		numTiles = 1;
		tileIndex = 4;
		_agentState = AgentState::STANDING;
	}

	//Increment animation speed;
	_animationTime += _animationSpeed;

	//Apply animation
	tileIndex = tileIndex + (int)_animationTime % numTiles;

	glm::vec4 uvRect = _spriteSheet.getUVs(tileIndex);

	if (_direction == LEFT) {
		uvRect.x += 1.0f / _spriteSheet.dims.x;
		uvRect.z *= -1.0f;
	}

	return uvRect;
}
