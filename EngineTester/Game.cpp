#include "Game.h"
#include <CandleLight_Engine\Components.h>
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

	_camera.init(1280, 720);
	_camera.setScale(30.0f);

	_renderSystem.init(_camera);

	GameObject* testObj = GameObjectManager::instance().newGameObjectBlueprint();
	testObj->transform.position = glm::vec2(-1.0f);
	testObj->transform.scale = glm::vec2(10.0f);
	testObj->name = "box";
	testObj->attachComponent(new SpriteComponent("Textures/boxTex.png"));

	GameObject* testLight = GameObjectManager::instance().newGameObjectBlueprint();
	testLight->transform.position = glm::vec2(-2.0f);
	testLight->transform.scale = glm::vec2(25.0f);
	testLight->name = "light";
	testLight->attachComponent(new LightComponent(Color(0, 255, 0, 255)));
	//testLight->attachComponent(new ScriptComponent("Scripts/main.lua"));
	testLight->attachComponent(new ScriptComponent("Scripts/script2.lua"));

	tex = ResourceManager::loadTexture("Textures/boxTex.png");
}

void Game::input()
{
	InputManager::instance()->update();

	GameObjectManager::instance().getGameObject(1)->transform.position = _camera.screenToWorldCoords(InputManager::instance()->getMousePos());
}

void Game::update()
{
	_camera.update();

	GameObjectManager::instance().updateGameObjects();
}

void Game::render()
{
	_renderSystem.render();

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
