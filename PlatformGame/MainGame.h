#pragma once

#include <Box2D\Box2D.h>

#include <CandleLight_Engine\Window.h>
#include <CandleLight_Engine\InputManager.h>
#include <CandleLight_Engine\Camera.h>
#include <CandleLight_Engine\Timing.h>
#include <CandleLight_Engine\SpriteBatch.h>

#include "StaticShader.h"
#include "Box.h"
#include "Human.h"
#include "Player.h"
#include "Bullet.h"
#include "Collision.h"

enum class GameState {PLAY, PAUSED, EXIT};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

private:
	Window _window;
	GameState _currentState;
	InputManager _inputManager;
	StaticShader _staticShader;
	Camera _camera;
	Timing _timer;
	SpriteBatch _spriteBatch;
	CollisionManager _collisionManager;

	Player _player;

	std::unique_ptr<b2World> _world;

	std::vector<Box> _boxes;
	std::vector<Human*> _humans;
	std::vector<Bullet*> _bullets;

	int _screenWidth = 1280;
	int _screenHeight = 720;

	void init();
	void input();
	void update();
	void render();
	void gameLoop();
	void cleanUp();
};

