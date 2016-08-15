#pragma once

#include "GUI.h"

class Icon : public GUI
{
public:
	Icon(GUI* prnt, glm::vec2& position, float size, const std::string& texPath, Color col);
	Icon(glm::vec2& position, float size, const std::string& texPath, Color col);
	Icon(const std::string& texPath);

	~Icon();
};

