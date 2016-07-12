#pragma once

#include "Camera.h"
#include "SpriteBatch.h"
#include "Texture.h"

#include <glm/glm.hpp>

//TODO: Make this the Widget class and add mouse over, and onClick calls and have button extend this class.
//TODO: Make button also have ability to parent a widget

class GUI
{
public:
	GUI(glm::vec2& pos, glm::vec2& dim, Texture& tex, Color& col);
	GUI();

	void render(SpriteBatch& spriteBatch);

	const glm::vec2& getPosition() { return position; }
	const glm::vec2& getDimension() { return dimension; }

	void setPosition(glm::vec2& newPos) { position = newPos; }
	
protected:
	glm::vec2 position, dimension;
	Color color;
	Texture texture;
	Camera camera;
};