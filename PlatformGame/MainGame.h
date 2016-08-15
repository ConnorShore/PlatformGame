#pragma once

#include <Box2D\Box2D.h>

#include <CandleLight_Engine\Window.h>
#include <CandleLight_Engine\InputManager.h>
#include <CandleLight_Engine\Camera.h>
#include <CandleLight_Engine\Timing.h>
#include <CandleLight_Engine\SpriteBatch.h>
#include <CandleLight_Engine\GUI.h>
#include <CandleLight_Engine\Panel.h>
#include <CandleLight_Engine\TiledPanel.h>
#include <CandleLight_Engine\Button.h>
#include <CandleLight_Engine\Background.h>
#include <CandleLight_Engine\Light.h>
#include <CandleLight_Engine\FrameBuffer.h>

#include "Box.h"
#include "Human.h"
#include "Player.h"
#include "Bullet.h"
#include "Collision.h"
#include "Ground.h"
#include "Tile.h"
#include "StaticShader.h"
#include "LightShader.h"


enum class GameState {PLAY, PAUSED, EXIT};
enum class GameControl {GAME, GUI};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

private:
	Window _window;
	GameState _currentState;
	GameControl _gameControl;
	InputManager _inputManager;
	StaticShader _staticShader;
	LightShader _lightShader;
	Camera _camera;
	Timing _timer;
	SpriteBatch _spriteBatch;
	SpriteBatch _tileBatch;
	SpriteBatch _guiBatch;
	SpriteBatch _backgroundBatch;
	SpriteBatch _lightBatch;
	CollisionManager _collisionManager;
	Ground _ground;
	FrameBuffer _lightFBuffer;
	Texture _lightMap;
	Player _player;
	Light light;
	Texture _lightTex;

	std::unique_ptr<b2World> _world;

	std::vector<Tile> _tiles;
	std::vector<Box> _boxes;
	std::vector<Human*> _humans;
	std::vector<Bullet*> _bullets;
	std::vector<GUI*> _guis;
	std::vector<Background> _backgrounds;
	std::vector<Light> _lights;

	int _screenWidth = 1920;
	int _screenHeight = 1080;

	void init();
	void input();
	void update();
	void renderGeometry();
	void renderLights();
	void render();
	void gameLoop();
	void cleanUp();

	void printWorking(int a);
	void printHello();
};

