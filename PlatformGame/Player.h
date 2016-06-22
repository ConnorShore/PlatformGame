#pragma once

#include <glm\glm.hpp>
#include <Box2D\Box2D.h>

#include "Agent.h"
#include "InputManager.h"
#include "Box.h"
#include "Texture.h"
#include "Weapon.h"

class Player : public Agent
{
public:
	Player();
	~Player();

	void init(b2World* world, const glm::vec2& position, const glm::vec2& dimension, const glm::vec2& uvDims, Texture& spriteSheet);
	void input(InputManager inputManager);
	void update();
	void render();

	inline Weapon getWeapon() const { return _weapon; }
	inline void setWeapon(Weapon& newWeapon) { _weapon = newWeapon; }

private:
	glm::vec2 _dimension, _uvDim;
	Box _collisionBox;
	Texture _spriteSheet;
	b2Body* _body;
	b2Fixture* _fixture;
	Weapon _weapon;
};