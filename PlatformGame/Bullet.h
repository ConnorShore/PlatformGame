#pragma once

#include "BulletDef.h"
#include <CandleLight_Engine\SpriteBatch.h>
#include "Agent.h"
#include "Damagable.h"

#include <vector>
#include <Box2D\Box2D.h>

class Bullet : public Damagable
{
public:
	Bullet(b2World* world, BulletDef& bulletDef);
	~Bullet(){}

	void update();
	void render(SpriteBatch& spriteBatch);

	b2Body* getBody() { return _body; }

private:
	Damagable* _damageStats = new Damagable;
	b2Body* _body;
	b2Fixture* _fixture;
	int _lifeCount = 0;
	float _size, _damage, _speed;
	Texture _texture;

	glm::vec2 _direction;

	const int LIFE_TIME = 100;
};