#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>

#include "Texture.h"
#include "Sprite.h"

class Entity
{
public:
	Entity();
	~Entity();

	void init(const glm::vec2& position, const glm::vec2& dimension, const Texture& texture, float depth = 1.0f);
	void update(float delta);
	void render();

	//TODO: MAster renderer

protected:
	glm::vec2 _position, _dimension;
	Texture _texture;
	float _depth;

private:
	GLuint _vaoID = 0, _vboID = 0;
	void setupSprite(float x, float y, float width, float height);
};

