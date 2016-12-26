#pragma once

#include <CandleLight_Engine\Window.h>
#include <CandleLight_Engine\Timing.h>
#include <CandleLight_Engine\InputManager.h>

class Game
{
public:
	Game();
	~Game();

	void run();

private:
	Window _window;
	Timing _timer;
	InputManager _inputManager;

	bool _isRunning;

	void init();
	void input();
	void update();
	void render();
	void gameLoop();
	void cleanUp();
};

