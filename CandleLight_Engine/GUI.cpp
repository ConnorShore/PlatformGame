#include "GUI.h"

GUI::GUI(glm::vec2 & pos, glm::vec2 & dim, Texture & tex, Color& col) : position(pos), dimension(dim), texture(tex), color(col)
{
}

GUI::GUI()
{
}

void GUI::render(SpriteBatch & spriteBatch)
{
	glm::vec4 destRect(position.x, position.y, dimension.x, dimension.y);
	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	spriteBatch.addToBatch(destRect, uvRect, 1.0f, texture.id, color);
}
