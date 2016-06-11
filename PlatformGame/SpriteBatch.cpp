#include "SpriteBatch.h"

#include <algorithm>

Sprite::Sprite(const glm::vec4& destRect, const glm::vec4& destUV, const Color& color, Texture& tex, float dep /*1.0f*/) : texture(tex), depth(dep)
{
	topLeft.setPosition(destRect.x, destRect.y + destRect.w);
	topLeft.setUV(destUV.x, destUV.y + destUV.w);
	topLeft.color = color;

	bottomLeft.setPosition(destRect.x, destRect.y);
	bottomLeft.setUV(destUV.x, destUV.y);
	bottomRight.color = color;

	bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
	bottomRight.setUV(destUV.x + destUV.z, destUV.y);
	bottomRight.color = color;

	topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
	topRight.setUV(destUV.x + destUV.z, destUV.y + destUV.w);
	topRight.color = color;
}

SpriteBatch::SpriteBatch()
{
}

SpriteBatch::~SpriteBatch()
{
}

void SpriteBatch::init()
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

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SpriteBatch::begin(SortType sortType /*TEXTURE*/)
{
	_sortType = sortType;
	_sprites.clear();
	_renderBatches.clear();
}

void SpriteBatch::addToBatch(glm::vec4 & destRect, glm::vec4 & destUV, Color & color, Texture texture, float depth)
{
	_sprites.emplace_back(destRect, destUV, color, texture, depth);
}

void SpriteBatch::render()
{
	glBindVertexArray(_vaoID);

	for (int i = 0; i < _renderBatches.size(); i++) {
		//glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _renderBatches[i].texture);
		glDrawArrays(GL_TRIANGLES, _renderBatches[i].offset, _renderBatches[i].numVertices);
	}

	glBindVertexArray(0);
}

void SpriteBatch::end()
{
	_sprPtrs.resize(_sprites.size());
	for (int i = 0; i < _sprPtrs.size(); i++) {
		_sprPtrs[i] = &_sprites[i];
	}

	sortSprites();
	createRenderBatches();
}

void SpriteBatch::sortSprites()
{
	switch (_sortType) {
	case SortType::TEXTURE:
		std::stable_sort(_sprPtrs.begin(), _sprPtrs.end(), sortTexture);
		break;
	case SortType::BACK_TO_FRONT:
		std::stable_sort(_sprPtrs.begin(), _sprPtrs.end(), sortBackToFront);
		break;
	case SortType::NONE:
		break;
	default:
		break;
	}
}

void SpriteBatch::createRenderBatches()
{
	if (_sprPtrs.empty())
		return;

	std::vector<Vertex> vertices;
	vertices.resize(_sprPtrs.size() * 6);
	int offset = 0;
	int cv = 0;

	_renderBatches.emplace_back(0, 6, _sprPtrs[0]->texture.id);
	vertices[cv++] = _sprPtrs[0]->topLeft;
	vertices[cv++] = _sprPtrs[0]->bottomLeft;
	vertices[cv++] = _sprPtrs[0]->bottomRight;
	vertices[cv++] = _sprPtrs[0]->bottomRight;
	vertices[cv++] = _sprPtrs[0]->topRight;
	vertices[cv++] = _sprPtrs[0]->topLeft;

	offset += 6;

	for (int cg = 1; cg < _sprPtrs.size(); cg++) {
		if (_sprPtrs[cg]->texture.id != _sprPtrs[cg - 1]->texture.id)	//Make sure there isn't a render batch already set up for current texture
			_renderBatches.emplace_back(offset, 6, _sprPtrs[cg]->texture.id);
		else
		{
			_renderBatches.back().numVertices += 6;
			vertices[cv++] = _sprPtrs[cg]->topLeft;
			vertices[cv++] = _sprPtrs[cg]->bottomLeft;
			vertices[cv++] = _sprPtrs[cg]->bottomRight;
			vertices[cv++] = _sprPtrs[cg]->bottomRight;
			vertices[cv++] = _sprPtrs[cg]->topRight;
			vertices[cv++] = _sprPtrs[cg]->topLeft;
			offset += 6;
		}
	}

	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);	//orphan the buffer
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());	//upload the data
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

bool SpriteBatch::sortBackToFront(Sprite * a, Sprite * b)
{
	return (a->depth < b->depth);
}

bool SpriteBatch::sortTexture(Sprite * a, Sprite * b)
{
	return (a->texture.id < b->texture.id);
}
