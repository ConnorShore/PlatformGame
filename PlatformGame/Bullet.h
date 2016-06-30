#pragma once

#include "BulletDef.h"
#include "SpriteBatch.h"

#include <vector>
#include <Box2D\Box2D.h>

class Bullet
{
public:
	Bullet(b2World* world, BulletDef& bulletDef);
	~Bullet(){}

	void update();
	void render(SpriteBatch& spriteBatch);

	bool isAlive() const { return _alive; }

private:
	b2Body* _body;
	b2Fixture* _fixture;
	int _lifeCount = 0;
	float _size, _damage, _speed;
	bool _alive;
	Texture _texture;

	glm::vec2 _direction;

	const int LIFE_TIME = 100;

	void checkCollision();
};