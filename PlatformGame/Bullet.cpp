#include "Bullet.h"

Bullet::Bullet(b2World* world, BulletDef& bulletDef /*Human* parent* <= for collision filtering*/)
{
	//Add collision filtering i.e 0x00, 0x02 for what bullets can collide with
	_size = bulletDef.size;
	_speed = bulletDef.speed;
	_texture = bulletDef.texture;
	_direction = bulletDef.direction;

	_damageStats->name = "bullet";
	_damageStats->damage = bulletDef.damage;

	//Implement body
	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	bodyDef.bullet = true;
	bodyDef.gravityScale = 0.0f;
	bodyDef.position.Set(bulletDef.position.x, bulletDef.position.y);
	bodyDef.linearVelocity.Set(bulletDef.direction.x * bulletDef.speed, bulletDef.direction.y * bulletDef.speed);
	_body = world->CreateBody(&bodyDef);
	_body->SetUserData(_damageStats);

	b2CircleShape circleShape;
	circleShape.m_radius = bulletDef.size / 2.0f;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	fixtureDef.friction = 0.0f;
	fixtureDef.density = 0.0f;
	fixtureDef.filter.categoryBits = bulletDef.collisionCategory;
	fixtureDef.filter.maskBits = bulletDef.collisionMask;
	_fixture = _body->CreateFixture(&fixtureDef);
}

void Bullet::update()
{
	_body->ApplyLinearImpulse(b2Vec2(_direction.x * _speed, _direction.y * _speed), _body->GetPosition());

	if (_damageStats->health <= 0.0f) _body->SetActive(false);

	if (_lifeCount > LIFE_TIME)
		_body->SetActive(false);
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