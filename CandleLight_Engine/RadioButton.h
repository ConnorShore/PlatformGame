#pragma once

#include "GUI.h"
#include "SpriteSheet.h"

#include <string>
#include <glm\glm.hpp>

class RadioButton : public GUI
{
public:
	const float SIZE = 0.1f;
	RadioButton(GUI* parent, glm::vec2& position, const std::string& texPath, Color color);
	RadioButton(glm::vec2& position, const std::string& texPath, Color color);
	
	void update() override;
	void onSelect();
	void onDeselect();

	void setGroup(int group) { _group = group; }
	int getGroup() const { return _group; }

	void setSelected(bool select) 
	{
		if (select)
			onSelect();
		else
			onDeselect();
	}

	bool isSelected() const { return _selected; }

	//Add vector of buttons so onSelect will go through list and deselect each other button in the vector
	//if no button group defined, add list of children for GUIS and have onSelect loop through those to deselect other buttons if this is selected
	
	~RadioButton();

private:
	SpriteSheet _spriteSheet;
	bool _selected;
	int _group = 0;
};

