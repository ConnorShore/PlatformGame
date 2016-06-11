#pragma once

#include "Vertex.h"
#include "Texture.h"

#include <vector>
#include <GL/glew.h>

class Sprite
{
public:
	Sprite();
	~Sprite();

	void init(float x, float y, float width, float height, Texture texture);
	void render();

private:
	GLuint _vaoID = 0, _vboID = 0;
	float _x, _y, _width, _height;
	Texture _texture;
};

