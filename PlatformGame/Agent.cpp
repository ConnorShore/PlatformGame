#include "Agent.h"

#include "ResourceManager.h"

Agent::Agent()
{
}


Agent::~Agent()
{
}

void Agent::init(b2World * world, const glm::vec2 & position, const glm::vec2 & dimension, const glm::ivec2 & sheetDims, const std::string & texPath)
{
	_texture = ResourceManager::loadTexture(texPath);
	_dimension = dimension;

	//_spriteSheet.init(_texture, sheetDims);
	
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	_body = world->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(dimension.x / 2.0f, dimension.y / 2.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.25f;
	_fixture = _body->CreateFixture(&fixtureDef);

	if (_vboID == 0)
		glGenBuffers(1, &_vboID);

	Vertex vertexData[6];
	vertexData[0].setPosition(_body->GetPosition().x + _dimension.x, _body->GetPosition().y + _dimension.y);
	vertexData[0].setUV(1.0f, 1.0f);
	vertexData[1].setPosition(_body->GetPosition().x, _body->GetPosition().y + _dimension.y);
	vertexData[1].setUV(0.0f, 1.0f);
	vertexData[2].setPosition(_body->GetPosition().x, _body->GetPosition().y);
	vertexData[2].setUV(0.0f, 0.0f);

	//Second Triangle
	vertexData[3].setPosition(_body->GetPosition().x, _body->GetPosition().y);
	vertexData[3].setUV(0.0f, 0.0f);
	vertexData[4].setPosition(_body->GetPosition().x + _dimension.x, _body->GetPosition().y);
	vertexData[4].setUV(1.0f, 0.0f);
	vertexData[5].setPosition(_body->GetPosition().x + _dimension.x, _body->GetPosition().y + _dimension.y);
	vertexData[5].setUV(1.0f, 1.0f);
}

void Agent::agentRender()
{
	Vertex vertexData[6];
	vertexData[0].setPosition(_body->GetPosition().x + _dimension.x, _body->GetPosition().y + _dimension.y);
	vertexData[0].setUV(1.0f, 1.0f);
	vertexData[1].setPosition(_body->GetPosition().x, _body->GetPosition().y + _dimension.y);
	vertexData[1].setUV(0.0f, 1.0f);
	vertexData[2].setPosition(_body->GetPosition().x, _body->GetPosition().y);
	vertexData[2].setUV(0.0f, 0.0f);

	//Second Triangle
	vertexData[3].setPosition(_body->GetPosition().x, _body->GetPosition().y);
	vertexData[3].setUV(0.0f, 0.0f);
	vertexData[4].setPosition(_body->GetPosition().x + _dimension.x, _body->GetPosition().y);
	vertexData[4].setUV(1.0f, 0.0f);
	vertexData[5].setPosition(_body->GetPosition().x + _dimension.x, _body->GetPosition().y + _dimension.y);
	vertexData[5].setUV(1.0f, 1.0f);

	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _texture.id);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

	render();

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
