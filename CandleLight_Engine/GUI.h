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
	RADIO_BUTTON,
	PANEL
};

class GUI
{
public:
	typedef std::function<void()> call;

	GUI(GUI* prnt, glm::vec2& pos, glm::vec2& dim, Texture& tex, Color& col);
	GUI(glm::vec2& pos, glm::vec2& dim, Texture& tex, Color& col);
	GUI();

	void render(SpriteBatch& spriteBatch);

	bool inBox(const glm::vec2& pos);

	virtual void update() {}

	const glm::vec2& getPosition() { return position; }
	const glm::vec2& getDimension() { return dimension; }
	const GUIType& getType() { return type; }
	GUI* getParent() { return parent; }

	void setPosition(glm::vec2& newPos) { position = newPos; }
	void setParent(GUI* prnt) { parent = prnt; }
	void setMouseOver(bool over) { mouseOver = over; }

	void addChild(GUI* child) { _children.push_back(child); }
	std::vector<GUI*>& getChildren() { return _children; }

	std::function<void()> callback() const { return eventCallback; }
	template<typename T, typename F, typename... Args>
	void subscribeEvent(T instance, F func, Args... args)
	{
		call temp = { std::bind(func, instance, args...) };
		eventCallback = temp;
	}
	
protected:
	GUI* parent = nullptr;
	glm::vec2 position, dimension;
	glm::vec4 uvRect;
	Color color;
	Texture texture;
	call eventCallback = NULL;
	GUIType type;
	bool mouseOver = false;

	std::vector<GUI*> _children;
};