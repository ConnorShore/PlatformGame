#include "SpriteBatch.h"

#include <algorithm>

Sprite::Sprite(const glm::vec4& destRect, const glm::vec4& uvRect, float Depth, GLuint Texture, const Color& color) :
	depth(Depth),
	texture(Texture) {

	topLeft.color = color;
	topLeft.setPosition(destRect.x, destRect.y + destRect.w);
	topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

	bottomLeft.color = color;
	bottomLeft.setPosition(destRect.x, destRect.y);
	bottomLeft.setUV(uvRect.x, uvRect.y);

	bottomRight.color = color;
	bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
	bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

	topRight.color = color;
	topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
	topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
}

Sprite::Sprite(const glm::vec4& destRect, const glm::vec4& uvRect, float Depth, GLuint Texture, const Color& color, float angle, int direction, bool gun) :
	depth(Depth),
	texture(Texture) {

	//Center points at origin
	glm::vec2 halfDims(destRect.z / 2.0f, destRect.w / 2.0f);
	glm::vec2 tl, tr, bl, br;

	if (gun) {
		if (direction == 1) {
			tl = glm::vec2(0, halfDims.y);
			tr = glm::vec2(halfDims.x * 2, halfDims.y);
			bl = glm::vec2(0, -halfDims.y);
			br = glm::vec2(halfDims.x * 2, -halfDims.y);

			tl = rotatePoint(tl, angle) + halfDims;
			tr = rotatePoint(tr, angle) + halfDims;
			bl = rotatePoint(bl, angle) + halfDims;
			br = rotatePoint(br, angle) + halfDims;
		}
		else {
			tl = glm::vec2(-halfDims.x * 2, halfDims.y);
			tr = glm::vec2(0, halfDims.y);
			bl = glm::vec2(-halfDims.x * 2, -halfDims.y);
			br = glm::vec2(0, -halfDims.y);

			tl = rotatePoint(tl, angle) + halfDims;
			tr = rotatePoint(tr, angle) + halfDims;
			bl = rotatePoint(bl, angle) + halfDims;
			br = rotatePoint(br, angle) + halfDims;
		}
	}
	else {
		tl = glm::vec2(-halfDims.x, halfDims.y);
		tr = glm::vec2(halfDims.x, halfDims.y);
		bl = glm::vec2(-halfDims.x, -halfDims.y);
		br = glm::vec2(halfDims.x, -halfDims.y);

		tl = rotatePoint(tl, angle) + halfDims;
		tr = rotatePoint(tr, angle) + halfDims;
		bl = rotatePoint(bl, angle) + halfDims;
		br = rotatePoint(br, angle) + halfDims;
	}

	topLeft.color = color;
	topLeft.setPosition(destRect.x + tl.x, destRect.y + tl.y);
	topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

	bottomLeft.color = color;
	bottomLeft.setPosition(destRect.x + bl.x, destRect.y + bl.y);
	bottomLeft.setUV(uvRect.x, uvRect.y);

	bottomRight.color = color;
	bottomRight.setPosition(destRect.x + br.x, destRect.y + br.y);
	bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

	topRight.color = color;
	topRight.setPosition(destRect.x + tr.x, destRect.y + tr.y);
	topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
}

glm::vec2 Sprite::rotatePoint(const glm::vec2& point, float angle)
{
	glm::vec2 newv;
	newv.x = point.x * cos(angle) - point.y * sin(angle);
	newv.y = point.x * sin(angle) + point.y * cos(angle);
	return newv;
}

SpriteBatch::SpriteBatch() : _vaoID(0), _vboID(0)
{
}

void SpriteBatch::init()
{
	createVertexArray();
}

void SpriteBatch::begin(SortType sortType /*TEXTURE*/)
{
	_sortType = sortType;
	_renderBatches.clear();

	_sprites.clear();
}

void SpriteBatch::end()
{
	_spritePointers.resize(_sprites.size());
	for (size_t i = 0; i < _sprites.size(); i++) {
		_spritePointers[i] = &_sprites[i];
	}

	sortSprites();
	createRenderBatches();
}

void SpriteBatch::addToBatch(const glm::vec4& destRect, const glm::vec4& uvRect, float depth, GLuint tex, const Color& color)
{
	_sprites.emplace_back(destRect, uvRect, depth, tex, color);
}

void SpriteBatch::addToBatch(const glm::vec4 & destRect, const glm::vec4 & uvRect, float depth, GLuint tex, const Color & color, float angle, int direction, bool gun)
{
	_sprites.emplace_back(destRect, uvRect, depth, tex, color, angle, direction, gun);
}

void SpriteBatch::addToBatch(const glm::vec4 & destRect, const glm::vec4 & uvRect, float depth, GLuint tex, const Color & color, const glm::vec2 & direction)
{
	const glm::vec2 right(1.0f, 0.0f);
	float angle = acos(glm::dot(right, direction));
	if (direction.y < 0.0f) angle = -angle;

	_sprites.emplace_back(destRect, uvRect, depth, tex, color, angle, 0, false);
}

void SpriteBatch::renderBatch()
{
	glBindVertexArray(_vaoID);

	for (int i = 0; i < _renderBatches.size(); i++) {
		glBindTexture(GL_TEXTURE_2D, _renderBatches[i].texture);
		glDrawArrays(GL_TRIANGLES, _renderBatches[i].offset, _renderBatches[i].numVertices);
	}

	glBindVertexArray(0);
}

void SpriteBatch::createRenderBatches()
{
	std::vector<Vertex> vertices;
	vertices.resize(_spritePointers.size() * 6);

	if (_spritePointers.empty())
		return;

	int currentVert = 0;
	int offset = 0;

	//Create first render batch
	_renderBatches.emplace_back(0, 6, _spritePointers[0]->texture);

	vertices[currentVert++] = _spritePointers[0]->topLeft;
	vertices[currentVert++] = _spritePointers[0]->bottomLeft;
	vertices[currentVert++] = _spritePointers[0]->bottomRight;
	vertices[currentVert++] = _spritePointers[0]->bottomRight;
	vertices[currentVert++] = _spritePointers[0]->topRight;
	vertices[currentVert++] = _spritePointers[0]->topLeft;
	offset += 6;

	//Loop through rest of Sprites
	for (int cg = 1; cg < _spritePointers.size(); cg++) {
		if (_spritePointers[cg]->texture != _spritePointers[cg - 1]->texture)	//Make sure there isn't a render batch already set up for current texture
			_renderBatches.emplace_back(offset, 6, _spritePointers[cg]->texture);
		else
			_renderBatches.back().numVertices += 6;

		vertices[currentVert++] = _spritePointers[cg]->topLeft;
		vertices[currentVert++] = _spritePointers[cg]->bottomLeft;
		vertices[currentVert++] = _spritePointers[cg]->bottomRight;
		vertices[currentVert++] = _spritePointers[cg]->bottomRight;
		vertices[currentVert++] = _spritePointers[cg]->topRight;
		vertices[currentVert++] = _spritePointers[cg]->topLeft;
		offset += 6;
	}

	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);	//orphan the buffer
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());	//upload the data
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SpriteBatch::createVertexArray()
{
	if (_vaoID == 0)
		glGenVertexArrays(1, &_vaoID);

	glBindVertexArray(_vaoID);

	if (_vboID == 0)
		glGenBuffers(1, &_vboID);

	glBindBuffer(GL_ARRAY_BUFFER, _vboID);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

	glBindVertexArray(0);
}

void SpriteBatch::sortSprites()
{
	switch (_sortType) {
	case SortType::BACK_TO_FRONT:
		std::stable_sort(_spritePointers.begin(), _spritePointers.end(), sortBackToFront);
		break;

	case SortType::FRONT_TO_BACK:
		std::stable_sort(_spritePointers.begin(), _spritePointers.end(), sortFrontToBack);
		break;

	case SortType::TEXTURE:
		std::stable_sort(_spritePointers.begin(), _spritePointers.end(), sortTexture);
		break;
	}
}

bool SpriteBatch::sortBackToFront(Sprite* a, Sprite* b)
{
	return (a->depth < b->depth);
}

bool SpriteBatch::sortFrontToBack(Sprite* a, Sprite* b)
{
	return (a->depth > b->depth);
}

bool SpriteBatch::sortTexture(Sprite* a, Sprite* b)
{
	return (a->texture < b->texture);
}

SpriteBatch::~SpriteBatch()
{
}