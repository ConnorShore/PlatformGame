#pragma once

#include "Camera.h"
#include "SpriteBatch.h"
#include "Texture.h"

#include <glm/glm.hpp>
#include <functional>

//TODO: Make this the Widget class and add mouse over, and onClick calls and have button extend this class.
//TODO: Make button also have ability to parent a widget

enum GUIType
{
	NONE,
	BUTTON,
	PANEL
};

class GUI
{
public:
	GUI(GUI* prnt, glm::vec2& pos, glm::vec2& dim, Texture& tex, Color& col);
	GUI(glm::vec2& pos, glm::vec2& dim, Texture& tex, Color& col);
	GUI();

	void render(SpriteBatch& spriteBatch);

	bool inBox(const glm::vec2& pos);

	const glm::vec2& getPosition() { return position; }
	const glm::vec2& getDimension() { return dimension; }
	const GUIType& getType() { return type; }
	GUI* getParent() { return parent; }

	void setPosition(glm::vec2& newPos) { position = newPos; }
	void setParent(GUI* prnt) { parent = prnt; }

	std::function<void()> callback() const { return eventCallback; }
	void subscribeEvent(const std::function<void()>& callback)
	{
		eventCallback = callback;
	}
	
protected:
	GUI* parent = nullptr;
	glm::vec2 position, dimension;
	Color color;
	Texture texture;
	std::function<void()> eventCallback = NULL;
	GUIType type;
};