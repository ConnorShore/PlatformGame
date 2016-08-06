#pragma once

#include <CandleLight_Engine\Window.h>
#include <CandleLight_Engine\InputManager.h>
#include <CandleLight_Engine\Camera.h>
#include <CandleLight_Engine\Timing.h>
#include <CandleLight_Engine\SpriteBatch.h>
#include <CandleLight_Engine\GUI.h>
#include <CandleLight_Engine\RadioButton.h>
#include <CandleLight_Engine\Checkbox.h>
#include <CandleLight_Engine\Button.h>
#include <CandleLight_Engine\Panel.h>
#include <CandleLight_Engine\SpriteFont.h>
#include <CandleLight_Engine\GUILabel.h>
#include <CandleLight_Engine\Background.h>
#include <CandleLight_Engine\StaticShader.h>

#include "GridShader.h"
#include "Box.h"
#include "Bullet.h"
#include "Collision.h"
#include "Ground.h"
#include "Level.h"
#include "Tile.h"

const int NO_TILE = -1;
const int NO_BOX = -1;
const int LEFT_BUTTON = 0;
const int RIGHT_BUTTON = 1;

enum class ObjectMode
{
	TILE,
	BOX,
	GROUND,
	SPAWN,	//< Player spawn points (Campfires)
	HUMAN
};

enum class SelectMode
{
	SELECT,
	PLACE
};

class EditorScreen
{
public:
	EditorScreen();
	~EditorScreen();

	void run();

private:
	std::unique_ptr<b2World> _world;

	Window _window;
	InputManager _inputManager;
	GridShader _gridShader;
	StaticShader _staticShader;
	Camera _camera;
	Timing _timer;
	SpriteBatch _spriteBatch;
	SpriteBatch _tileBatch;
	SpriteBatch _guiBatch;
	SpriteBatch _hudBatch;
	SpriteBatch _backgroundBatch;
	CollisionManager _collisionManager;
	Texture _playerTex;
	Texture _nodeTex;
	Texture _sheetTex;
	Ground _ground;
	SpriteFont* _spriteFont;

	ObjectMode _objectMode = ObjectMode::TILE;
	SelectMode _selectMode = SelectMode::PLACE;

	bool _isRunning;
	bool _guiControl = false;
	bool _showBackgrounds = true;
	bool _gridSnap = true;
	bool _drag = false;

	std::vector<GUI*> _guis;
	std::vector<GUILabel> _guiLabels;
	std::vector<Tile> _tiles;
	std::vector<Box> _boxes;
	std::vector<Background> _backgrounds;

	bool _mouseButtons[2];

	int _tileIndices[128];
	int _currentTileIndex = 0;

	int _selectedTile = NO_TILE;
	int _selectedBox = NO_BOX;

	int _screenWidth = 1600;
	int _screenHeight = 960;

	void init();
	void updateGUI();
	void input();
	void update();
	void render();
	void gameLoop();
	void cleanUp();

	void updateMouseDown(const SDL_Event& evnt);
	void updateMouseWheel(const SDL_Event& evnt);

	void saveLevel(const std::string& fileName, const std::string& texSheet);
	void switchSelectMode(SelectMode& mode);
	void switchObjectMode(ObjectMode& mode);
	void toggleBackground();
	void toggleGridSnap();
	void toggleDrag();
	
	void clear();

	void printHello() { printf("Hello\n"); }

	//Player _player;
	//std::vector<Human*> _humans;
};

