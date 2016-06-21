#include "Player.h"



Player::Player()
{
}

Player::~Player()
{
}

void Player::init(b2World* world, const glm::vec2& position, const glm::vec2& dimension, const glm::vec2& uvDims, Texture& spriteSheet)
{
	_collisionBox.init(world, position, dimension, spriteSheet);
}

void Player::input(InputManager inputManager)
{
}

void Player::update()
{
}

void Player::render()
{
}