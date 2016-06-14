#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <Box2D\Box2D.h>

#include "Texture.h"
#include "Sprite.h"

class Box
{
public:
	Box();
	~Box();

	void init(b2World* world, const glm::vec2& position, const glm::vec2& dimension, const Texture& texture, float depth = 1.0f);
	void update();
	void render();

	glm::vec2 getDimension() const { return _dimension; }
	Texture getTexture() const { return _texture; }
	GLuint getVboID() const { return _vboID; }

	void setVboID(GLuint vboID) { _vboID = vboID; }

private:
	glm::vec2 _dimension;
	Texture _texture;
	float _depth;
	GLuint _vboID = 0;
	b2Body* _body = nullptr;
	b2Fixture* _fixture = nullptr;
};