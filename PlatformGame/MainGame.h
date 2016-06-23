#pragma once

#include <Box2D\Box2D.h>

#include "Window.h"
#include "InputManager.h"
#include "StaticShader.h"
#include "Camera.h"
#include "Timing.h"
#include "Box.h"
#include "Agent.h"
#include "Player.h"

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
	Player _player;

	std::unique_ptr<b2World> _world;

	std::vector<Box> _boxes;
	std::vector<Agent> _agents;

	int _screenWidth = 1280;
	int _screenHeight = 720;

	void init();
	void input();
	void update();
	void render();
	void gameLoop();
	void cleanUp();
};

