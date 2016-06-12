#include "MainGame.h"
#include "ResourceManager.h"

#include <SDL\SDL.h>
#include <GL\glew.h>
#include <random>

MainGame::MainGame()
{
	//TODO: Make entity system
	//Improve render system
	//TODO: Make messaging system (Make a world)
	//TODO: Add box2D physics
}

MainGame::~MainGame()
{
}

void MainGame::init()
{
	_window.createWindow("Platform Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight);
	_currentState = GameState::PLAY;

	_camera.init(_screenWidth, _screenHeight);

	std::mt19937 randomGen;
	std::uniform_real_distribution<float> xDist(-100.0f, 100.0f);
	std::uniform_real_distribution<float> yDist(-100.0f, 150.0f);

	Texture tex = ResourceManager::loadTexture("Textures/boxTex.png");

	for (int i = 0; i < 5; i++) {
		Entity entity;
		entity.init(glm::vec2(xDist(randomGen), yDist(randomGen)), glm::vec2(1.0f, 1.0f), tex);
		_renderer.initEntity(entity);
		_entities.push_back(entity);
	}

	_staticShader.init("Shaders/staticShader.vert", "Shaders/staticShader.frag");
	_staticShader.bindAttributes();
}

void MainGame::input()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_QUIT:
			//Send message to maingame to exit
			exit(0);
			break;
		case SDL_KEYDOWN:
			_inputManager.keyPressed(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			_inputManager.keyReleased(evnt.key.keysym.sym);
			break;
		}
	}

	if (_inputManager.isKeyDown(SDLK_w)) {
		_camera.setPosition(glm::vec2(_camera.getPosition().x, _camera.getPosition().y + 10.0f * _timer.getDeltaTime()));
	}
	else if (_inputManager.isKeyDown(SDLK_s)) {
		_camera.setPosition(glm::vec2(_camera.getPosition().x, _camera.getPosition().y - 10.0f * _timer.getDeltaTime()));
	}
	if (_inputManager.isKeyDown(SDLK_a)) {
		_camera.setPosition(glm::vec2(_camera.getPosition().x - 10.0f * _timer.getDeltaTime(), _camera.getPosition().y));
	}
	else if (_inputManager.isKeyDown(SDLK_d)) {
		_camera.setPosition(glm::vec2(_camera.getPosition().x + 10.0f * _timer.getDeltaTime(), _camera.getPosition().y));
	}

	if (_inputManager.isKeyDown(SDLK_q)) {
		_camera.setScale(_camera.getScale() + 5.0f * _timer.getDeltaTime());
	}
	else if (_inputManager.isKeyDown(SDLK_e)) {
		_camera.setScale(_camera.getScale() - 5.0f * _timer.getDeltaTime());
	}
}

void MainGame::update()
{
	_camera.update();
}

void MainGame::render()
{
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//_staticShader.start();
	//_staticShader.getUniformLocations();
	//_staticShader.loadPMatrix(_camera.getCameraMatrix());
	//_staticShader.loadTexture();
	//for(int i = 0; i < _entities.size(); i++)
	//	_entities[i].render();

	//_staticShader.stop();

	_renderer.render(_staticShader, _camera);

	for (int i = 0; i < _entities.size(); i++)
		_renderer.processEntity(_entities[i]);

	_window.swapWindow();
}

void MainGame::gameLoop()
{
	_timer.TimeInit();

	while (_currentState != GameState::EXIT) {
		_timer.FpsLimitInit();
		_timer.calcDeltaTime();

		input();
		update();
		render();

		_timer.CalculateFPS(true);
	}
}

void MainGame::cleanUp()
{
	_window.destroyWindow();
	SDL_Quit();
	exit(0);
}

void MainGame::run()
{
	init();
	gameLoop();
	cleanUp();
}