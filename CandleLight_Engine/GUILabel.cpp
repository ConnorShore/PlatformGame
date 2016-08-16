#include "GUILabel.h"


GUILabel::GUILabel(GUI * parent, const char* text, float size, Color color, /* WHITE */ LabelPosition labelPos /* ABOVE */)
{
	_parent = parent;
	_position = glm::vec2(parent->getPosition().x + (parent->getDimension().x / 2.0f), parent->getPosition().y + (parent->getDimension().y / 2.0f));
	_labelText = text;
	_size = size;
	_labelColor = color;
	_labelPos = labelPos;

	_spriteFont = new SpriteFont(_labelFont, 32);

	switch (_labelPos) {
		case LabelPosition::ABOVE:
			_justification = Justification::MIDDLE;
			_drawPos = glm::vec2(_position.x, _position.y + parent->getDimension().y/2 + TEXT_PADDING);
			break;
		case LabelPosition::BELOW:
			_justification = Justification::MIDDLE;
			_drawPos = glm::vec2(_position.x, _position.y - parent->getDimension().y/2 - TEXT_PADDING);
			break;
		case LabelPosition::RIGHT:
			_justification = Justification::LEFT;
			_drawPos = glm::vec2(_position.x + parent->getDimension().x, _position.y);
			break;
		case LabelPosition::LEFT:
			_justification = Justification::RIGHT;
			_drawPos = glm::vec2(_position.x - parent->getDimension().x, _position.y);
			break;
		case LabelPosition::CENTER:
			_justification = Justification::MIDDLE;
			_drawPos = _position;
			break;
	}
}

GUILabel::~GUILabel()
{
	
}

void GUILabel::render(SpriteBatch & spriteBatch, Camera& camera)
{
	if (_parent->isVisible()) {
		char buffer[256];
		sprintf_s(buffer, _labelText);
		_spriteFont->draw(spriteBatch, buffer, _drawPos, glm::vec2(_size * TEXT_SCALE), 1.0f, _labelColor, _justification);
	}
}
