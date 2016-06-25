#pragma once

#include "Vertex.h"

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <vector>

enum class SortType {
	NONE,
	BACK_TO_FRONT,
	FRONT_TO_BACK,
	TEXTURE
};

class Sprite {
public:
	Sprite() {};
	Sprite(const glm::vec4& destRect, const glm::vec4& uvRect, float Depth, GLuint Texture, const Color& color);
	Sprite(const glm::vec4& destRect, const glm::vec4& uvRect, float Depth, GLuint Texture, const Color& color, float angle);

	Vertex topLeft, bottomLeft, topRight, bottomRight;
	GLuint texture;
	float depth;

private:
	glm::vec2 rotatePoint(glm::vec2 point, float angle);
};

class RenderBatch {
public:
	RenderBatch(GLuint Offset, GLuint NumVerts, GLuint Texture) : offset(Offset), numVertices(NumVerts), texture(Texture) {}

	GLuint offset, numVertices, texture;
};

class SpriteBatch
{
public:
	SpriteBatch();
	~SpriteBatch();

	void init();
	void begin(SortType sortType = SortType::TEXTURE);
	void end();
	void addToBatch(const glm::vec4& destRect, const glm::vec4& uvRect, float depth, GLuint tex, const Color& color);
	void addToBatch(const glm::vec4& destRect, const glm::vec4& uvRect, float depth, GLuint tex, const Color& color, float angle);
	void renderBatch();

private:
	GLuint _vaoID, _vboID;
	SortType _sortType;

	std::vector<RenderBatch> _renderBatches;
	std::vector<Sprite> _sprites;
	std::vector<Sprite*>  _spritePointers;

	void createRenderBatches();
	void createVertexArray();
	void sortSprites();

	static bool sortBackToFront(Sprite* a, Sprite* b);
	static bool sortFrontToBack(Sprite* a, Sprite* b);
	static bool sortTexture(Sprite* a, Sprite* b);
};