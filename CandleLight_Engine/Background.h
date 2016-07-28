#pragma once

#include "SpriteBatch.h"
#include "Texture.h"
#include "Camera.h"

class Background
{
public:
	Background();
	~Background();

	void init(const std::string& filePath, const glm::vec2& position, const glm::vec2& dimension, int depth, int numRepeats);
	void update(Camera& camera);
	void render(SpriteBatch& spriteBatch);

private:
	glm::vec2 _position, _dimension, _offset;
	Texture _texture;
	int _depth, _numRepeats;
};