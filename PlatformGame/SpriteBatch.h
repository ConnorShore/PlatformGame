#pragma once

#include "Vertex.h"
#include "Texture.h"

#include <glm\glm.hpp>
#include <GL\glew.h>
#include <vector>

enum class SortType {NONE, BACK_TO_FRONT, TEXTURE};

class Sprite
{
public:
	Sprite() {}
	Sprite(const glm::vec4& destRect, const glm::vec4& destUV, const Color& color, Texture& tex, float dep = 1.0f);

	Vertex topLeft, bottomLeft, bottomRight, topRight;
	Texture texture;
	float depth;
};

class RenderBatch
{
public:
	RenderBatch(GLuint offst, GLuint vertices, GLuint tex) : offset(offst), numVertices(vertices), texture(tex) {}
	GLuint offset, numVertices, texture;
};

class SpriteBatch
{
public:
	SpriteBatch();
	~SpriteBatch();

	void init();
	void begin(SortType sortType = SortType::TEXTURE);
	void addToBatch(glm::vec4& destRect, glm::vec4& destUV, Color& color, Texture texture, float depth = 1.0f);
	void render();
	void end();

private:
	std::vector<Sprite> _sprites;
	std::vector<Sprite*> _sprPtrs;
	std::vector<RenderBatch> _renderBatches;

	GLuint _vaoID = 0, _vboID = 0;
	SortType _sortType;

	void sortSprites();
	void createRenderBatches();
	static bool sortBackToFront(Sprite* a, Sprite* b);
	static bool sortTexture(Sprite* a, Sprite* b);
};

