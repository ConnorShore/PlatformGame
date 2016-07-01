#pragma once

#include "Texture.h"
#include "Human.h"
#include "InputManager.h"
#include "Camera.h"
#include "BulletDef.h"

#include <glm\glm.hpp>

enum class FireMode {SEMI_AUTO, AUTOMATIC, BURST};

class Human;

class Weapon
{
public:
	Weapon(const glm::vec2& position, const glm::vec2& dimension, const glm::vec2& origin, const std::string& filePath);
	Weapon() {}

	void update(InputManager inputManager, Camera& camera);
	void render(SpriteBatch& spriteBatch);
	bool shoot();

	void setParent(Human* parent) { _parent = parent; }
	void setFireCount(float count) { _fireCount = count; }
	void resetFireCount() { _fireCount = 0.0f; }

	BulletDef& getBulletDef() { return _bulletDef; }
	float getFireRate() const { return _fireRate; }

protected:
	Human* _parent;
	b2Body* _body;
	glm::vec2 _position, _dimension, _origin;
	Texture _texture;
	float _damage, _fireRate, _angle, _fireCount = 1000.0f;
	int _bulletCount, _magazineSize;
	BulletDef _bulletDef;
	bool _canShoot = true;
};