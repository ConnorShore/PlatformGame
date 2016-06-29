#include "Bullet.h"

Bullet::Bullet(b2World* world, BulletDef& bulletDef /*Human* parent* <= for collision filtering*/)
{
	//Add collision filtering i.e 0x00, 0x02 for what bullets can collide with
	_size = bulletDef.size;
	_damage = bulletDef.damage;
	_speed = bulletDef.speed;
	_texture = bulletDef.texture;
	_direction = bulletDef.direction;
	_alive = true;

	//Implement body
	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	bodyDef.gravityScale = 0.0f;
	bodyDef.position.Set(bulletDef.position.x, bulletDef.position.y);
	bodyDef.linearVelocity.Set(bulletDef.direction.x * bulletDef.speed, bulletDef.direction.y * bulletDef.speed);
	_body = world->CreateBody(&bodyDef);

	b2CircleShape circleShape;
	circleShape.m_radius = bulletDef.size / 2.0f;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	fixtureDef.friction = 0.0f;
	fixtureDef.density = 0.0f;
	_fixture = _body->CreateFixture(&fixtureDef);
}

void Bullet::update()
{
	_body->ApplyLinearImpulse(b2Vec2(_direction.x * _speed, _direction.y * _speed), _body->GetPosition());

	if (_lifeCount > LIFE_TIME)
		_alive = false;
	else
		_lifeCount++;
}

void Bullet::render(SpriteBatch & spriteBatch)
{
	glm::vec4 destRect;
	destRect.x = _body->GetPosition().x - _size / 2.0f;
	destRect.y = _body->GetPosition().y - _size / 2.0f;
	destRect.z = destRect.w = _size;
	spriteBatch.addToBatch(destRect, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), 0.0f, _texture.id, Color(255, 255, 255, 255));
}