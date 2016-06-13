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

	b2Vec2 gravity(0, -20.0f);
	_world = std::make_unique<b2World>(gravity);

	_camera.init(_screenWidth, _screenHeight);

	std::mt19937 randomGen;
	std::uniform_real_distribution<float> xDist(-10.0f, 10.0f);
	std::uniform_real_distribution<float> yDist(-10.0f, 15.0f);

	Texture tex = ResourceManager::loadTexture("Textures/boxTex.png");

	//Setup ground
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -15.0f);
	b2Body* groundBody = _world->CreateBody(&groundBodyDef);
	b2PolygonShape groundShape;
	groundShape.SetAsBox(50.0f, 5.0f);
	groundBody->CreateFixture(&groundShape, 0.0f);

	//Setup entities
	for (int i = 0; i < 50; i++) {
		Entity entity;
		entity.init(_world.get(), glm::vec2(xDist(randomGen), yDist(randomGen)), glm::vec2(1.0f, 1.0f), tex);
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
		_camera.setPosition(glm::vec2(_camera.getPosition().x, _camera.getPosition().y + 10.0f));
	}
	else if (_inputManager.isKeyDown(SDLK_s)) {
		_camera.setPosition(glm::vec2(_camera.getPosition().x, _camera.getPosition().y - 10.0f));
	}
	if (_inputManager.isKeyDown(SDLK_a)) {
		_camera.setPosition(glm::vec2(_camera.getPosition().x - 10.0f, _camera.getPosition().y));
	}
	else if (_inputManager.isKeyDown(SDLK_d)) {
		_camera.setPosition(glm::vec2(_camera.getPosition().x + 10.0f, _camera.getPosition().y));
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
	_world->Step(1 / 60.0f, 6, 2);
}

void MainGame::render()
{
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	_staticShader.start();
	_staticShader.getUniformLocations();
	_staticShader.loadPMatrix(_camera.getCameraMatrix());
	_staticShader.loadTexture();

	for(int i = 0; i < _entities.size(); i++)
		_entities[i].render();

	_staticShader.stop();

	_window.swapWindow();
}

void MainGame::gameLoop()
{
	_timer.TimeInit();

	while (_currentState != GameState::EXIT) {
		_timer.FpsLimitInit();

		input();
		update();
		render();

		_timer.LimitFPS(60.0f);
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