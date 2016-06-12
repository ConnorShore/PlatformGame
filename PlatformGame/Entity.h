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

	glm::vec2 getPosition() const { return _position; }
	glm::vec2 getDimension() const { return _dimension; }
	Texture getTexture() const { return _texture; }
	GLuint getVaoID() const { return _vaoID; }
	GLuint getVboID() const { return _vboID; }

	void setVaoID(GLuint vaoID) { _vaoID = vaoID; }
	void setVboID(GLuint vboID) { _vboID = vboID; }

protected:
	glm::vec2 _position, _dimension;
	Texture _texture;
	float _depth;
	GLuint _vaoID = 0, _vboID = 0;

private:
	void setupSprite(float x, float y, float width, float height);
};

