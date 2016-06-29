#include "MainGame.h"
#include "ResourceManager.h"
#include "AK47.h"

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
	_camera.setScale(37.0f);

	std::mt19937 randomGen;
	std::uniform_real_distribution<float> xDist(-10.0f, 10.0f);
	std::uniform_real_distribution<float> yDist(-10.0f, 15.0f);

	_spriteBatch.init();

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
		box.init(_world.get(), glm::vec2(xDist(randomGen), yDist(randomGen)), glm::vec2(1.0f, 1.0f), tex);
		_boxes.push_back(box);
	}

	_player.humanInit(_world.get(), glm::vec2(0.0f, 15.0f), glm::vec2(1.0f, 1.8f), glm::vec2(10, 1), "Textures/ss_player_base.png");
	_player.addWeapon(new AK47(_player.getPosition(), glm::vec2(1.0f, -0.75f)));
	_player.addWeapon(new AK47(_player.getPosition(), glm::vec2(2.2f, 1.55f), glm::vec2(1.0f, -0.75f)));
	_humans.push_back(&_player);

	_staticShader.init("Shaders/staticShader.vert", "Shaders/staticShader.frag");
	_staticShader.bindAttributes();
}

void MainGame::input()
{
	_inputManager.update();
	_player.input(_inputManager, _camera);
}

void MainGame::update()
{
	for (auto& human : _humans) {
		if (human->isShooting()) {
			Bullet* bullet = new Bullet(_world.get(), human->getCurrentWeapon()->getBulletDef());
			_bullets.push_back(bullet);
		}

		human->humanUpdate();
	}

	_camera.setPosition(glm::vec2(_player.getPosition().x + _player.getDimension().x / 2.0f, _player.getPosition().y + _player.getDimension().y / 2.0f));
	_camera.update();

	for (auto& bullet : _bullets)
		bullet->update();

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

	_spriteBatch.begin();

	for (int i = 0; i < _humans.size(); i++)
		_humans[i]->humanRender(_spriteBatch);

	for (int i = 0; i < _bullets.size(); i++)
		_bullets[i]->render(_spriteBatch);

	for(int i = 0; i < _boxes.size(); i++)
		_boxes[i].render(_spriteBatch);

	_spriteBatch.end();
	_spriteBatch.renderBatch();

	_staticShader.stop();

	_window.swapWindow();
}

void MainGame::gameLoop()
{
	_timer.TimeInit();

	while (_currentState != GameState::EXIT) {
		_timer.FpsLimitInit();
		_timer.calcDeltaTime();

		update();
		input();
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