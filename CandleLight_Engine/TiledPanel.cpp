#include "TiledPanel.h"
#include "ResourceManager.h"


TiledPanel::TiledPanel(GUI * prnt, glm::vec2 & position, glm::vec2 & dimension, const std::string & texPath, Color col, float tileSize) 
	: GUI(prnt, position, dimension, ResourceManager::loadTexture(texPath), col)
{
	type = TILED_PANEL;
	_tileSize = tileSize;
	_maxSize = getMaxSize();
}

TiledPanel::TiledPanel(glm::vec2 & position, glm::vec2 & dimension, const std::string & texPath, Color col, float tileSize)
	: GUI(position, dimension, ResourceManager::loadTexture(texPath), col)
{
	type = TILED_PANEL;
	_tileSize = tileSize;
	_maxSize = getMaxSize();
}

TiledPanel::~TiledPanel()
{
}

void TiledPanel::render(SpriteBatch & spriteBatch)
{
	glm::vec4 destRect(position.x, position.y, dimension.x, dimension.y);
	spriteBatch.addToBatch(destRect, uvRect, 1.0f, texture.id, color);

	for (auto& tile : _tiles) {
		tile.render(spriteBatch);
	}
}

void TiledPanel::addTile(Icon& tile)
{
	if (_tiles.size() < _maxSize) {
		tile.setDimension(glm::vec2(_tileSize));
		int num = _tiles.size();
		tile.setPosition(createLayout(num));
		tile.setParent(this);
		_tiles.push_back(tile);
	}
	else
		printf("Tile pane full\n");
}

glm::vec2 TiledPanel::createLayout(int index)
{
	glm::vec2 pos;
	int rowNum, colNum;
	float padX, padY;
	float sizeX, sizeY;
	rowNum = ((int)(dimension.x / _tileSize) - 2);
	colNum = ((int)(dimension.y / _tileSize) - 2);
	padX = (dimension.x - (rowNum * _tileSize)) / rowNum;
	padY = (dimension.y - (colNum * _tileSize)) / colNum;
	sizeX = _tileSize + padX;
	sizeY = _tileSize + padY;
	pos.x = (index % rowNum) * (sizeX / dimension.x) + (padX / 2.0f);
	pos.y = ((1.0f - (sizeY / dimension.y)) + (index / rowNum) * -(sizeY / dimension.y)) + padY;

	return pos;
}

int TiledPanel::getMaxSize()
{
	int rowNum, colNum;
	rowNum = ((int)(dimension.x / _tileSize) - 2);
	colNum = ((int)(dimension.y / _tileSize) - 2);
	return rowNum * colNum;
}
