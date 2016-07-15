#pragma once

#include <CandleLight_Engine\Window.h>
#include <CandleLight_Engine\InputManager.h>
#include <CandleLight_Engine\Camera.h>
#include <CandleLight_Engine\Timing.h>
#include <CandleLight_Engine\SpriteBatch.h>
#include <CandleLight_Engine\GUI.h>
#include <CandleLight_Engine\Button.h>
#include <CandleLight_Engine\Panel.h>

#include "StaticShader.h"
#include "Box.h"
//#include "Human.h"
//#include "Player.h"
#include "Bullet.h"
#include "Collision.h"
#include "Ground.h"
#include "Tile.h"

const int NO_TILE = -1;
const int NO_BOX = -1;
const int LEFT_BUTTON = 0;
const int RIGHT_BUTTON = 1;

enum class ObjectMode
{
	TILE,
	BOX,
	GROUND
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
	StaticShader _staticShader;
	Camera _camera;
	Timing _timer;
	SpriteBatch _spriteBatch;
	SpriteBatch _tileBatch;
	SpriteBatch _guiBatch;
	CollisionManager _collisionManager;
	Ground _ground;
	Texture _sheetTex;
	
	ObjectMode _objectMode = ObjectMode::TILE;
	SelectMode _selectMode = SelectMode::PLACE;

	bool _isRunning;
	bool _guiControl = false;

	std::vector<GUI*> _guis;
	std::vector<Tile> _tiles;
	std::vector<Box> _boxes;

	bool _mouseButtons[2];

	int _tileIndices[64];
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
	void clear();

	//Player _player;
	//std::vector<Human*> _humans;
};

