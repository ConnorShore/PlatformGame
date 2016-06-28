#include "Player.h"

#include <SDL\SDL.h>

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

void Player::input(InputManager inputManager, Camera& camera)
{
	if (camera.screenToWorldCoords(inputManager.getMousePos()).x >= _body->GetPosition().x) _direction = RIGHT;
	else _direction = LEFT;

	if (inputManager.isKeyDown(SDLK_d)) {
		_body->ApplyForceToCenter(b2Vec2(100.0f, 0.0f));
		_agentState = AgentState::RUNNING;
	}
	else if (inputManager.isKeyDown(SDLK_a)) {
		_body->ApplyForceToCenter(b2Vec2(-100.0f, 0.0f));
		_agentState = AgentState::RUNNING;
	}
	else {
		_body->SetLinearVelocity(b2Vec2(_body->GetLinearVelocity().x * 0.7f, _body->GetLinearVelocity().y));
	}

	if (inputManager.isKeyDown(SDLK_w)) {
		if (_canJump && _onGround) {
			_body->ApplyLinearImpulse(b2Vec2(0.0f, 5.0), _body->GetPosition());
			_canJump = false;
		}
	}

	if (_body->GetLinearVelocity().x > MAX_SPEED) {
		_body->SetLinearVelocity(b2Vec2(MAX_SPEED, _body->GetLinearVelocity().y));
	}
	if (_body->GetLinearVelocity().x < -MAX_SPEED) {
		_body->SetLinearVelocity(b2Vec2(-MAX_SPEED, _body->GetLinearVelocity().y));
	}

	//Weapon selection
	if (inputManager.isKeyDown(SDLK_1)) {
		_currentWeapon = _primaryWeapon;
	}
	else if (inputManager.isKeyDown(SDLK_2)) {
		_currentWeapon = _secondaryWeapon;
	}

	//Shooting
	if (inputManager.isKeyDown(SDL_BUTTON_LEFT)) {
		//implement shooting
	}

	_currentWeapon->update(inputManager, camera);
}

void Player::render()
{
	
}

void Player::shoot(const glm::vec2& direction)
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

		if (_direction == RIGHT)
			_animationSpeed = glm::abs(velocity.x) * 0.04f;
		else
			_animationSpeed = -glm::abs(velocity.x) * 0.04f;

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

	glm::vec4 uvRect = _spritesheet.getUVs(tileIndex);

	if (_direction == LEFT) {
		uvRect.x += 1.0f / _spritesheet.dims.x;
		uvRect.z *= -1.0f;
	}

	return uvRect;
}
