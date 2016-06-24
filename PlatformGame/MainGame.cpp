#include "MainGame.h"
#include "ResourceManager.h"

#include <SDL\SDL.h>
#include <GL\glew.h>
#include <random>

MainGame::MainGame()
{
	
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

	//Setup boxes
	for (int i = 0; i < 50; i++) {
		Box box;
		box.init(_world.get(), glm::vec2(xDist(randomGen), yDist(randomGen)), glm::vec2(2.0f, 1.0f), tex);
		_boxes.push_back(box);
	}

	_player = new Player();
	_player->agentInit(_world.get(), glm::vec2(0.0f, 15.0f), glm::vec2(1.25f, 2.0f), glm::vec2(1.25f, 2.0f), glm::vec2(10, 1), "Textures/ss_player_base.png");
	_agents.push_back(_player);

	_staticShader.init("Shaders/staticShader.vert", "Shaders/staticShader.frag");
	_staticShader.bindAttributes();
}

void MainGame::input()
{
	_inputManager.update();
	_player->input(_inputManager);
}

void MainGame::update()
{
	for (auto& agent : _agents)
		agent->update();

	_camera.setPosition(glm::vec2(_player->getPosition().x + _player->getDimension().x / 2.0f, _player->getPosition().y + _player->getDimension().y / 2.0f));
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

	for (auto& agent : _agents)
		agent->agentRender();

	for(int i = 0; i < _boxes.size(); i++)
		_boxes[i].render();

	_staticShader.stop();

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

		_timer.LimitFPS(60.0f);
		_timer.CalculateFPS(false);
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