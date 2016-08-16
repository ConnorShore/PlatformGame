#include "TiledPanel.h"
#include "ResourceManager.h"


TiledPanel::TiledPanel(GUI * prnt, glm::vec2 & position, glm::vec2 & dimension, const std::string & texPath, Color col, glm::vec2& tileSize)
	: GUI(prnt, position, dimension, ResourceManager::loadTexture(texPath), col)
{
	type = TILED_PANEL;
	_tileSize = tileSize;
	_maxSize = getMaxSize();
	createLayout();
}

TiledPanel::TiledPanel(glm::vec2 & position, glm::vec2 & dimension, const std::string & texPath, Color col, glm::vec2& tileSize)
	: GUI(position, dimension, ResourceManager::loadTexture(texPath), col)
{
	type = TILED_PANEL;
	_tileSize = tileSize;
	_maxSize = getMaxSize();
	createLayout();
}

TiledPanel::~TiledPanel()
{
}

void TiledPanel::addTile(Icon& tile)
{
	if (_tiles.size() < _maxSize) {
		tile.setDimension(glm::vec2(_tileSize));
		int num = _tiles.size();
		tile.setPosition(setLayout(num));
		tile.setParent(this);
		tile.setVisible(visible);
		_tiles.push_back(tile);
	}
	else{}
		//printf("Tile pane full\n");
}

glm::vec2 TiledPanel::setLayout(int index)
{
	//Split this up so row calcs aren't every new element, just once
	glm::vec2 pos;
	float sizeX, sizeY;
	sizeX = _tileSize.x + _padding.x;
	sizeY = _tileSize.y + _padding.y;
	pos.x = (index % _gridNums.x) * (sizeX / dimension.x) + (_padding.x/1.5f);
	pos.y = ((1.0f - (sizeY / dimension.y)) + (index / _gridNums.x) * -(sizeY / dimension.y)) + _padding.y/2.0f;
	return pos;
}

void TiledPanel::createLayout()
{
	_padding.x = (dimension.x - (_gridNums.x * _tileSize.x)) / _gridNums.x;
	_padding.y = (dimension.y - (_gridNums.y * _tileSize.y)) / _gridNums.y;
}

int TiledPanel::getMaxSize()
{
	glm::ivec2 reduction;
	reduction.x = (int)((dimension.x * 0.25f) / _tileSize.x);
	reduction.y = (int)((dimension.y * 0.25f) / _tileSize.y);

	_gridNums.x = ((int)(dimension.x / _tileSize.x) - reduction.x);
	_gridNums.y = ((int)(dimension.y / _tileSize.y) - reduction.y);
	return _gridNums.x * _gridNums.y;
}
