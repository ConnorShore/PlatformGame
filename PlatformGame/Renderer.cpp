#include "Renderer.h"



Renderer::Renderer()
{
	//Create a hash function for Texture
}

Renderer::~Renderer()
{
}

//void Renderer::renderEntities()
//{
//	for (auto it = _entities.begin(); it != _entities.end(); it++) {
//		prepareTexture(it->first);
//		std::vector<Entity> batch = it->second;
//		for (Entity e : batch) {
//			glDrawArrays(GL_TRIANGLES, 0, 6);
//		}
//		unbind();
//	}
//}

//void Renderer::processEntity(Entity& entity)
//{
//	//Create entity batch
//	Texture texture = entity.getTexture();
//	std::unordered_map<unsigned int, std::vector<Entity>>::iterator it;
//	std::vector<Entity> batch = it->second;
//	if (batch.size() != 0)
//		batch.push_back(entity);
//	else {
//		std::vector<Entity> newBatch;
//		newBatch.push_back(entity);
//		_entities.insert(std::make_pair(texture.id, newBatch));
//	}
//}
void Renderer::renderEntities()
{
	for (int i = 0; i < _entities.size(); i++) {
		prepareTexture(_entities[i][0].getTexture());
		for (int j = 0; j < _entities[i].size(); i++) {
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
		unbind();
	}
}

void Renderer::processEntity(Entity& entity)
{
	bool found = false;
	Texture texture = entity.getTexture();
	for (int i = 0; i < _entities.size(); i++) {
		if (texture.id == _entities[i][0].getTexture().id) {
			_entities[i].push_back(entity);
			found = true;
			break;
		}
	}

	if (!found) {
		std::vector<Entity> newBatch;
		newBatch.push_back(entity);
		_entities.push_back(newBatch);
	}
}

void Renderer::render(StaticShader& shader, Camera& camera)
{
	shader.start();
	shader.getUniformLocations();
	shader.loadPMatrix(camera.getCameraMatrix());
	shader.loadTexture();
	renderEntities();
	shader.stop();
}

void Renderer::initEntity(Entity& entity)
{
	glm::vec4 destRect(entity.getPosition(), entity.getDimension());
	glm::vec4 destUV(0.0f, 0.0f, 1.0f, 1.0f);
	GLuint vaoID = entity.getVaoID();
	GLuint vboID = entity.getVboID();

	if (vaoID == 0)
		glGenVertexArrays(1, &vaoID);

	if (vboID == 0)
		glGenBuffers(1, &vboID);

	entity.setVaoID(vaoID);
	entity.setVboID(vboID);

	Vertex vertexData[6];
	vertexData[0].setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
	vertexData[0].setUV(destUV.x + destUV.z, destUV.y + destUV.w);
	vertexData[1].setPosition(destRect.x, destRect.y + destRect.w);
	vertexData[1].setUV(destUV.x, destUV.y + destUV.w);
	vertexData[2].setPosition(destRect.x, destRect.y);
	vertexData[2].setUV(destUV.x, destUV.y);

	//Second Triangle
	vertexData[3].setPosition(destRect.x, destRect.y);
	vertexData[3].setUV(destUV.x, destUV.y);
	vertexData[4].setPosition(destRect.x + destRect.z, destRect.y);
	vertexData[4].setUV(destUV.x + destUV.z, destUV.y);
	vertexData[5].setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
	vertexData[5].setUV(destUV.x + destUV.z, destUV.y + destUV.w);

	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Renderer::prepareTexture(Texture texture)
{
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.id);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
}

void Renderer::unbind()
{
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}