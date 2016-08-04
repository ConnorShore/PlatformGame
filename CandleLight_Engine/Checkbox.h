#pragma once

#include "GUI.h"
#include "SpriteSheet.h"

#include <string>
#include <glm\glm.hpp>

class Checkbox : public GUI
{
public:
	Checkbox(GUI* parent, glm::vec2& position, const std::string& texPath, Color color);
	Checkbox(glm::vec2& position, const std::string& texPath, Color color);
	~Checkbox();

	void update() override;
	void onClick();

	void setSelected(bool select) 
	{
		_selected = select;
		if(_selected)
			uvRect = _spriteSheet.getUVs(1);
		else
			uvRect = _spriteSheet.getUVs(0);
	}

	bool isSelected() const { return _selected; }

	//Add vector of buttons so onSelect will go through list and deselect each other button in the vector
	//if no button group defined, add list of children for GUIS and have onSelect loop through those to deselect other buttons if this is selected


private:
	SpriteSheet _spriteSheet;
	bool _selected;
};

