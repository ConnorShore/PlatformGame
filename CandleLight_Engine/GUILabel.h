#pragma once

#include <glm\glm.hpp>

#include "SpriteFont.h"
#include "GUI.h"

enum class LabelPosition
{
	LEFT, RIGHT, CENTER, ABOVE, BELOW
};

class GUILabel
{
public:
	GUILabel(GUI* parent, const char* text, float size, Color color = Color(255,255,255,255), LabelPosition labelPos = LabelPosition::ABOVE);
	~GUILabel();

	const glm::vec2& getPosition() { return _position; }

	void setText(const char* text) { _labelFont = text; }
	void setFont(const char* font) { _labelFont = font; }

	void render(SpriteBatch& spriteBatch, Camera& camera);

private:
	GUI* _parent;
	SpriteFont* _spriteFont;
	Color _labelColor;
	LabelPosition _labelPos;
	Justification _justification;
	glm::vec2 _position, _drawPos;
	float _size;
	const char* _labelText;
	const char* _labelFont = "Fonts/BEBAS.ttf";

	const float TEXT_SCALE = 0.001f;
	const float TEXT_PADDING = 0.025f;
};