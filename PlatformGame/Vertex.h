#pragma once

#include <GL/glew.h>

struct Position
{
	float x, y;
};

struct Color
{
	GLubyte r, g, b, a;
};

struct UV
{
	float u, v;
};

struct Vertex
{
	Position pos;
	Color color;
	UV uv;

	inline void setPosition(float xPos, float yPos) { pos.x = xPos; pos.y = yPos; }
	inline void setColor(GLubyte rVal, GLubyte gVal, GLubyte bVal, GLubyte aVal) { color.r = rVal; color.g = gVal; color.b = bVal; color.a = aVal; }
	inline void setUV(float uVal, float vVal) { uv.u = uVal, uv.v = vVal; }
};