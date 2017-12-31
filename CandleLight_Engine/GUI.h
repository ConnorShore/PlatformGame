#pragma once

#include "Camera.h"
#include "SpriteBatch.h"
#include "Texture.h"
#include "SpriteFont.h"

#include <glm/glm.hpp>
#include <functional>

//TODO: Add isActive so you can hide/show GUI elements

enum GUIType
{
	NONE,
	ICON,
	BUTTON,
	RADIO_BUTTON,
	CHECKBOX,
	PANEL,
	TILED_PANEL
};

class GUI
{
public:
	typedef std::function<void()> call;

	GUI(GUI* prnt, glm::vec2& pos, glm::vec2& dim, Texture& tex, Color& col, bool autoPos = true);
	GUI(glm::vec2& pos, glm::vec2& dim, Texture& tex, Color& col);
	GUI();

	virtual void render(SpriteBatch& spriteBatch);

	bool inBox(const glm::vec2& pos);

	virtual void update() {}

	const glm::vec2& getPosition() { return position; }
	const glm::vec2& getDimension() { return dimension; }
	const GUIType& getType() { return type; }
	GUI* getParent() { return parent; }
	bool isVisible() { return visible; }
	Color getColor() { return color; }

	void setPosition(glm::vec2& newPos) { position = newPos; }
	void setDimension(glm::vec2& newDim) { dimension = newDim; }
	void setParent(GUI* prnt) 
	{ 
		parent = prnt; 
		position = (position * parent->getDimension() + parent->getPosition());
	}
	void setMouseOver(bool over) { mouseOver = over; }
	void setVisible(bool vis) 
	{ 
		visible = vis; 
		if (_children.size() > 0) {
			for (int i = 0; i < _children.size(); i++) {
				_children[i]->setVisible(vis);
			}
		}
	}

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
	bool visible = true;

	std::vector<GUI*> _children;
};