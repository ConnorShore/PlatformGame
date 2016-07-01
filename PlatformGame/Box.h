#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <Box2D\Box2D.h>

#include "Texture.h"
#include "SpriteBatch.h"
#include "Collision.h"
#include "Damagable.h";

class Box
{
public:
	Box();
	~Box();

	void init(b2World* world, const glm::vec2& position, const glm::vec2& dimension, const Texture& texture, float depth = 1.0f);
	void update();
	void render(SpriteBatch& spriteBatch);

	glm::vec2 getDimension() const { return _dimension; }
	Texture getTexture() const { return _texture; }
	b2Body* getBody() const { return _body; }
	bool isAlive() const { return _isAlive; }

private:
	Damagable* _damageStats = new Damagable;
	glm::vec2 _dimension;
	Texture _texture;
	float _depth;
	b2Body* _body = nullptr;
	b2Fixture* _fixture = nullptr;
	bool _isAlive = true;
};