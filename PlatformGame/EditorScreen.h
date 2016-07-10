#pragma once

#include <CandleLight_Engine\Window.h>
#include <CandleLight_Engine\InputManager.h>
#include <CandleLight_Engine\Camera.h>
#include <CandleLight_Engine\Timing.h>
#include <CandleLight_Engine\SpriteBatch.h>

#include "StaticShader.h"
#include "Box.h"
//#include "Human.h"
//#include "Player.h"
#include "Bullet.h"
#include "Collision.h"
#include "Ground.h"
#include "Tile.h"

#define NONE 0

enum class ObjectMode
{
	TILE,
	BOX
};

enum class SelectMODE
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
	Window _window;
	InputManager _inputManager;
	StaticShader _staticShader;
	Camera _camera;
	Timing _timer;
	SpriteBatch _spriteBatch;
	SpriteBatch _tileBatch;
	CollisionManager _collisionManager;
	Ground _ground;

	bool _isRunning;

	//Player _player;

	std::vector<Tile> _tiles;
	std::vector<Box> _boxes;
	//std::vector<Human*> _humans;
	int _selectedTile = NONE;
	int _selectedBox = NONE;

	int _screenWidth = 1600;
	int _screenHeight = 960;

	void init();
	void input();
	void update();
	void render();
	void gameLoop();
	void cleanUp();
};

