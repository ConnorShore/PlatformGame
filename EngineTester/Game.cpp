#include "Game.h"
#include <CandleLight_Engine\SpriteComponent.h>
#include <CandleLight_Engine\ResourceManager.h>

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

	GameObject* testObj = GameObjectManager::instance().newGameObjectBlueprint();
	testObj->transform.position = glm::vec2(-1.0f);
	testObj->transform.scale = glm::vec2(10.0f);
	testObj->attachComponent(new SpriteComponent("Textures/boxTex.png"));

	_renderSystem.init();

	_camera.init(1280, 720);
	_camera.setScale(60.0f);


	tex = ResourceManager::loadTexture("Textures/boxTex.png");
}

void Game::input()
{
	_inputManager.update();
}

void Game::update()
{
	_camera.update();

	GameObjectManager::instance().updateGameObjects();
}

void Game::render()
{
	_renderSystem.prepare();

	_renderSystem.render(_camera);

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
