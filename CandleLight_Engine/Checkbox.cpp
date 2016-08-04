#include "Checkbox.h"

#include "ResourceManager.h"

Checkbox::Checkbox(GUI * parent, glm::vec2 & position, const std::string & texPath, Color color) : GUI(parent, position, glm::vec2(0.02f, 0.03f), ResourceManager::loadTexture(texPath), color)
{
	type = CHECKBOX;
	_spriteSheet.init(texture, glm::vec2(2, 1));
}

Checkbox::Checkbox(glm::vec2 & position, const std::string & texPath, Color color) : GUI(position, glm::vec2(0.02f, 0.03f), ResourceManager::loadTexture(texPath), color)
{
	type = CHECKBOX;
	_spriteSheet.init(texture, glm::vec2(2, 1));
}

void Checkbox::update()
{

}

void Checkbox::onClick()
{
	if (_selected) {
		_selected = false;
		uvRect = _spriteSheet.getUVs(0);
	}
	else {
		_selected = true;
		uvRect = _spriteSheet.getUVs(1);
	}

	if (eventCallback != NULL)
		eventCallback();
}

Checkbox::~Checkbox()
{
}
