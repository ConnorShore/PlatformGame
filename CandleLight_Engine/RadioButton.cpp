#include "RadioButton.h"

#include "ResourceManager.h"

RadioButton::RadioButton(GUI * parent, glm::vec2 & position, const std::string & texPath, Color color) : GUI(parent, position, glm::vec2(0.1f), ResourceManager::loadTexture(texPath), color)
{
	type = RADIO_BUTTON;
	_spriteSheet.init(texture, glm::vec2(2, 1));
	//uvRect = _spriteSheet.getUVs(0);
}

RadioButton::RadioButton(glm::vec2 & position, const std::string & texPath, Color color) : GUI(position, glm::vec2(SIZE), ResourceManager::loadTexture(texPath), color)
{
	type = RADIO_BUTTON;
	_spriteSheet.init(texture, glm::vec2(2, 1));
	uvRect = _spriteSheet.getUVs(0);
}

void RadioButton::update()
{

}

void RadioButton::onSelect()
{
	for(auto& button : parent->getChildren()) {
		if(button->getType() == RADIO_BUTTON && button != this) {
			RadioButton* b = static_cast<RadioButton*>(button);
			b->onDeselect();
		}
	}

	uvRect = _spriteSheet.getUVs(1);
	_selected = true;

	if(eventCallback != NULL)
		eventCallback();
}

void RadioButton::onDeselect()
{
	_selected = false;
	uvRect = _spriteSheet.getUVs(0);
}

RadioButton::~RadioButton()
{
}
