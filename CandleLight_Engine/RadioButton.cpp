#include "RadioButton.h"

#include "ResourceManager.h"

RadioButton::RadioButton(GUI * parent, glm::vec2 & position, const std::string & texPath, Color color) : GUI(parent, position, glm::vec2(0.02f, 0.03f), ResourceManager::loadTexture(texPath), color)
{
	type = RADIO_BUTTON;
	_spriteSheet.init(texture, glm::vec2(2, 1));
}

RadioButton::RadioButton(glm::vec2 & position, const std::string & texPath, Color color) : GUI(position, glm::vec2(0.02f, 0.03f), ResourceManager::loadTexture(texPath), color)
{
	type = RADIO_BUTTON;
	_spriteSheet.init(texture, glm::vec2(2, 1));
}

void RadioButton::update()
{
	
}

void RadioButton::onSelect()
{
	if (parent != nullptr) {
		for (auto& button : parent->getChildren()) {
			if (button->getType() == RADIO_BUTTON && button != this) {
				RadioButton* b = static_cast<RadioButton*>(button);
				if(b->getGroup() == _group)
					b->onDeselect();
			}
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
