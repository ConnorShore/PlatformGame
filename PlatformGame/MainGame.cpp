#include "MainGame.h"

#include <CandleLight_Engine\ResourceManager.h>

#include <SDL\SDL.h>
#include <GL\glew.h>
#include <random>

#include "AK47.h"
#include "Level.h"

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
	_gameControl = GameControl::GAME;

	b2Vec2 gravity(0, -20.0f);
	_world = std::make_unique<b2World>(gravity);
	_world.get()->SetContactListener(&_collisionManager);

	_camera.init(_screenWidth, _screenHeight);
	_camera.setScale(65.0f);

	_tileBatch.init();
	_spriteBatch.init();
	_guiBatch.init();
	_backgroundBatch.init();

	Background back1;
	back1.init("Textures/Mountains/sky.png", glm::vec2(-22.0f), glm::vec2(100, 25), 0, 5);
	_backgrounds.push_back(back1);
	Background back2;
	back2.init("Textures/Mountains/mountains_back.png", glm::vec2(-22.0f), glm::vec2(100, 25), 1, 5);
	_backgrounds.push_back(back2);
	Background back3;
	back3.init("Textures/Mountains/mountains_front.png", glm::vec2(-22.0f), glm::vec2(100, 25), 2, 5);
	_backgrounds.push_back(back3);

	Texture tex = ResourceManager::loadTexture("Textures/boxTex.png");

	_player.humanInit(_world.get(), glm::vec2(0.0f, -8.0f), glm::vec2(1.0f, 1.9f), glm::vec2(10, 1), "Textures/ss_player_base.png");
	_player.addWeapon(new AK47(_player.getPosition(), glm::vec2(1.0f, -0.75f)));
	_player.addWeapon(new AK47(_player.getPosition(), glm::vec2(2.2f, 1.55f), glm::vec2(1.0f, -0.75f)));
	_humans.push_back(&_player);

	Level::loadLevel("level1.txt", _world.get(), _tiles, _ground, _boxes);
	_ground.init(_world.get(), _ground.getVertices().size());

	_staticShader.init("Shaders/staticShader.vert", "Shaders/staticShader.frag");
	_staticShader.bindAttributes();
}

void MainGame::input()
{
	_inputManager.update();

	//Check button input
	for (int i = 0; i < _guis.size(); i++) {
		glm::vec2 pos = _camera.screenToGLCoords(_inputManager.getMousePos());
		GUIType t = _guis[i]->getType();
		if (_guis[i]->inBox(pos)) {
			_gameControl = GameControl::GUI;
			if (_inputManager.isKeyDown(SDL_BUTTON_LEFT)) {
				switch (t) {
					case BUTTON:
						Button* button;
						button = static_cast<Button*>(_guis[i]);
						button->onClick();
						break;
					case NONE:
						break;
				}
			}
		}
		else {
			_gameControl = GameControl::GAME;
		}
	}

	_gameControl = GameControl::GAME;

	//Player input
	_player.input(_inputManager, _camera);

	if (_inputManager.isKeyDown(SDLK_e)) {
		_camera.setScale(_camera.getScale() + 0.25f);
	}

	if (_inputManager.isKeyDown(SDLK_q)) {
		_camera.setScale(_camera.getScale() - 0.25f);
	}
}

void MainGame::update()
{
	for (int i = 0; i < _collisionManager.bodiesToDestroy.size(); i++) {
		_collisionManager.bodiesToDestroy[i]->SetActive(false);
	}
	_collisionManager.bodiesToDestroy.clear();

	for (int i = 0; i < _boxes.size(); i++) {
		_boxes[i].update();
		if (_boxes[i].isAlive() == false) {
			_world->DestroyBody(_boxes[i].getBody());
			_boxes[i] = _boxes.back();
			_boxes.pop_back();
			i--;
		}
	}

	for (auto& human : _humans) {
		if (human->isShooting()) {
			Bullet* bullet = new Bullet(_world.get(), human->getCurrentWeapon()->getBulletDef());
			_bullets.push_back(bullet);
		}
		human->humanUpdate();
	}

	_camera.setPosition(glm::vec2(_player.getPosition().x + _player.getDimension().x / 2.0f, _player.getPosition().y + _player.getDimension().y / 2.0f));
	_camera.update();

	for (auto& back : _backgrounds)
		back.update(_camera);

	for (int i = 0; i < _bullets.size(); i++) {
		if (_bullets[i]->getBody()->IsActive() == false) {
			_world->DestroyBody(_bullets[i]->getBody());
			delete _bullets[i];
			_bullets[i] = _bullets.back();
			_bullets.pop_back();
			i--;
		}
		else {
			_bullets[i]->update();
		}
	}

	_world->Step(1 / 60.0f, 6, 2);
}

void MainGame::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_staticShader.start();
	_staticShader.getUniformLocations();
	_staticShader.loadPMatrix(_camera.getCameraMatrix());
	_staticShader.loadTexture();

	//Backgrounds
	_backgroundBatch.begin(SortType::BACK_TO_FRONT);

	for (auto& back : _backgrounds)
		back.render(_backgroundBatch);

	_backgroundBatch.end();
	_backgroundBatch.renderBatch();

	//Tiles
	_tileBatch.begin();

	for (int i = 0; i < _tiles.size(); i++) {
		_tiles[i].render(_tileBatch);
	}
	_tileBatch.end();
	_tileBatch.renderBatch();

	//Sprites
	_spriteBatch.begin();

	for (int i = 0; i < _humans.size(); i++)
		_humans[i]->humanRender(_spriteBatch);

	for (int i = 0; i < _bullets.size(); i++)
		_bullets[i]->render(_spriteBatch);

	for(int i = 0; i < _boxes.size(); i++)
		_boxes[i].render(_spriteBatch);

	_spriteBatch.end();
	_spriteBatch.renderBatch();

	_staticShader.loadPMatrix(_camera.getTransformationMatrix());

	_guiBatch.begin();

	for (int i = 0; i < _guis.size(); i++) {
		_guis[i]->render(_guiBatch);	//< TODO: Make follow camera at all times
	}

	_guiBatch.end();
	_guiBatch.renderBatch();

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
	b2World* raw = _world.release();
	delete raw;

	for (int i = 0; i < _humans.size(); i++)
		delete _humans[i];

	for (int i = 0; i < _bullets.size(); i++)
		delete _bullets[i];

	for (int i = 0; i < _guis.size(); i++)
		delete _guis[i];

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

void MainGame::printWorking(int a)
{
	printf("Working %d\n", a);
}

void MainGame::printHello()
{
	printf("Hello\n");
}