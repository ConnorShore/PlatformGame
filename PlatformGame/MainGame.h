#pragma once

#include "Window.h"
#include "InputManager.h"
#include "StaticShader.h"
#include "Camera.h"
#include "Timing.h"
#include "Entity.h"

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

	std::vector<Entity> _entities;

	int _screenWidth = 1280;
	int _screenHeight = 720;

	void init();
	void input();
	void update();
	void render();
	void gameLoop();
	void cleanUp();
};

