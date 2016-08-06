#pragma once

#include <glm\glm.hpp>

#include "Vertex.h"

struct Light
{
	Light(glm::vec2& pos, float intense, float sz, Color& col) : position(pos), intensity(intense), size(sz), color(col) {}
	Light() : position(glm::vec2(0.0f)), intensity(0.0f), size(0.0f), color(Color(255, 255, 255, 255)) {}

	glm::vec2 position;
	float intensity;
	float size;
	Color color;
};