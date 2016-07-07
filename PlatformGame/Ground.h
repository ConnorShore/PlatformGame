#pragma once

#include <glm\glm.hpp>
#include <vector>
#include <Box2D\Box2D.h>

#include "Collision.h"

class Ground
{
public:
	Ground();
	~Ground();

	void init(b2World* world, const int size);

	void addVertex(const glm::vec2& vertex);

	const std::vector<glm::vec2>& getVertices() { return _vertices; }

private:
	b2Body* _body;
	std::vector<glm::vec2> _vertices;
};

