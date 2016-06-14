//#pragma once
//
//#include "Box.h"
//#include "StaticShader.h"
//#include "Camera.h"
//#include "Texture.h"
//
//#include <unordered_map>
//#include <GL/glew.h>
//
//class Renderer
//{
//public:
//	Renderer();
//	~Renderer();
//
//	void initEntity(Box& entity);
//	void processEntity(Box& entity);
//	void render(StaticShader& shader, Camera& camera);
//
//private:
//	GLuint _vaoID = 0, _vboID = 0;
//	std::vector< std::vector<Box> > _entities;
//
//	void prepareTexture(Texture texture);
//	void renderEntities();
//	void unbind();
//};
//
