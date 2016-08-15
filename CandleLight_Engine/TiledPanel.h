#pragma once

#include "GUI.h"
#include "Icon.h"

class TiledPanel : public GUI
{
public:
	TiledPanel(GUI* prnt, glm::vec2& position, glm::vec2& dimension, const std::string& texPath, Color col, float tileSize);
	TiledPanel(glm::vec2& position, glm::vec2& dimension, const std::string& texPath, Color col, float tileSize);
	~TiledPanel();

	void render(SpriteBatch& spriteBatch) override;
	void addTile(Icon& tile);

private:
	std::vector<Icon> _tiles;
	int _maxSize;
	float _tileSize, _padding;

	glm::vec2 createLayout(int index);
	int getMaxSize();
};

