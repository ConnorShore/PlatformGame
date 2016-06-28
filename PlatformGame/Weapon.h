#pragma once

#include "Texture.h"
#include "Human.h"
#include "InputManager.h"
#include "Camera.h"

#include <glm\glm.hpp>

class Human;

class Weapon
{
public:
	Weapon(const glm::vec2& position, const glm::vec2& dimension, const glm::vec2& origin, const std::string& filePath);
	Weapon() {}

	void update(InputManager inputManager, Camera& camera);
	void render(SpriteBatch& spriteBatch);

	Human* _parent;
	b2Body* _body;
	glm::vec2 _position, _dimension, _origin;
	Texture _texture;
	float _damage, _fireRate, _angle;
	int _bulletCount, _magazineSize;
};