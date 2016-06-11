#pragma once

#include "Entity.h"
#include "StaticShader.h"
#include "Camera.h"
#include "Texture.h"

#include <unordered_map>
#include <GL/glew.h>

class Renderer
{
public:
	Renderer();
	~Renderer();

	void initEntity(Entity& entity);
	void processEntity(Entity& entity);
	void render(StaticShader& shader, Camera& camera);

private:
	GLuint _vaoID = 0, _vboID = 0;

	std::unordered_map<unsigned int, std::vector<Entity>> _entities;

	void prepareTexture(unsigned int textureID);
	void renderEntities();
	void unbind();
};

