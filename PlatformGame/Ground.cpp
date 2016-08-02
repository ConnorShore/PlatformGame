#include "Ground.h"



Ground::Ground()
{
}


Ground::~Ground()
{
}

void Ground::init(b2World * world, const int size)
{
	//Setup ground
	b2BodyDef groundBodyDef;
	_body = world->CreateBody(&groundBodyDef);

	b2Vec2* vs = new b2Vec2[size];
	for (int i = 0; i < size; i++) {
		vs[i] = b2Vec2(_vertices[i].x, _vertices[i].y);
	}
	b2ChainShape chain;
	chain.CreateChain(vs, size);

	b2FixtureDef fixDef;
	fixDef.shape = &chain;
	fixDef.filter.categoryBits = CATEGORY_ENVIRONMENT;
	fixDef.filter.maskBits = MASK_ALL;
	_body->CreateFixture(&fixDef);
}

void Ground::addVertex(const glm::vec2& vertex)
{
	_vertices.push_back(vertex);
}
