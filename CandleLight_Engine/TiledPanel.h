#pragma once

#include "GUI.h"
#include "Icon.h"

enum class Sort {UP, DOWN};

class TiledPanel : public GUI
{
public:
	TiledPanel(GUI* prnt, glm::vec2& position, glm::vec2& dimension, const std::string& texPath, Color col, glm::vec2& tileSize, Sort sort = Sort::DOWN);
	TiledPanel(glm::vec2& position, glm::vec2& dimension, const std::string& texPath, Color col, glm::vec2& tileSize, Sort sort = Sort::DOWN);
	~TiledPanel();

	//void render(SpriteBatch& spriteBatch) override;
	void addTile(Icon& tile);

private:
	std::vector<Icon> _tiles;
	int _maxSize;
	glm::vec2 _tileSize;
	glm::ivec2 _gridNums;
	glm::vec2 _padding;
	Sort _sortType;

	glm::vec2 setLayout(int index);
	void createLayout();
	int getMaxSize();
};

