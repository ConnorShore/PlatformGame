#pragma once

#include "GUI.h"

class Button : public GUI
{
public:
	Button(GUI* prnt, glm::vec2& position, glm::vec2& dimension, const std::string& texPath, Color col);
	Button(glm::vec2& position, glm::vec2& dimension, const std::string& texPath, Color col);
	~Button();

	void onClick();

private:

};

