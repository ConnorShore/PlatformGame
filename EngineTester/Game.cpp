#include "Game.h"



Game::Game()
{
}

Game::~Game()
{
}

void Game::init()
{
	_isRunning = true;

	_window.createWindow("Engine Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720);
	_window.setBackgroundColor(Color(0, 50, 120, 255));
}

void Game::input()
{
	_inputManager.update();
}

void Game::update()
{

}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_window.swapWindow();
}

void Game::gameLoop()
{
	while (_isRunning) {
		_timer.FpsLimitInit();
		_timer.calcDeltaTime();

		update();
		input();
		render();

		_timer.LimitFPS(60.0f);
		_timer.CalculateFPS(false);
	}
}

void Game::cleanUp()
{
	_window.destroyWindow();
	SDL_Quit();
}

void Game::run()
{
	init();
	gameLoop();
	cleanUp();
}
