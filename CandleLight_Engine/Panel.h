#pragma once

#include "GUI.h"

class Panel : public GUI
{
public:
	Panel(GUI* prnt, glm::vec2& position, glm::vec2& dimension, const std::string& texPath, Color col);
	Panel(glm::vec2& position, glm::vec2& dimension, const std::string& texPath, Color col);
	~Panel();

private:

};

