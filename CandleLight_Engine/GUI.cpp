#include "GUI.h"



GUI::GUI(GUI * prnt, glm::vec2 & pos, glm::vec2 & dim, Texture & tex, Color & col)
{
	parent = prnt;
	parent->addChild(this);
	position = (pos * parent->getDimension() + parent->getPosition());
	dimension = dim;
	texture = tex;
	color = col;
	uvRect = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	visible = prnt->isVisible();
}

GUI::GUI(glm::vec2 & pos, glm::vec2 & dim, Texture & tex, Color& col) : position(pos), dimension(dim), texture(tex), color(col), visible(true)
{
	uvRect = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
}

GUI::GUI()
{
}

void GUI::render(SpriteBatch & spriteBatch)
{
	if (visible) {
		glm::vec4 destRect(position.x, position.y, dimension.x, dimension.y);
		spriteBatch.addToBatch(destRect, uvRect, 1.0f, texture.id, color);
	}
}

bool GUI::inBox(const glm::vec2& pos)
{
	return (pos.x > position.x && pos.y > position.y && pos.x < (position.x + dimension.x) && pos.y < (position.y + dimension.y));
}