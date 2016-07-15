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
	_camera.setScale(37.0f);

	std::mt19937 randomGen;
	std::uniform_real_distribution<float> xDist(-10.0f, 10.0f);
	std::uniform_real_distribution<float> yDist(-10.0f, 2.0f);

	_tileBatch.init();
	_spriteBatch.init();
	_guiBatch.init();

	Texture tex = ResourceManager::loadTexture("Textures/boxTex.png");

	_ground.addVertex(glm::vec2(-10.0f, -10.0f));
	_ground.addVertex(glm::vec2(-3.0f, -10.0f));
	_ground.addVertex(glm::vec2(-3.0f, -11.0f));
	_ground.addVertex(glm::vec2(21.0f, -11.0f));
	_ground.addVertex(glm::vec2(21.0f, -10.0f));
	_ground.addVertex(glm::vec2(26.0f, -10.0f));
	_ground.init(_world.get(), _ground.getVertices().size());

	//Setup boxes
	for (int i = 0; i < 10; i++) {
		Box box;
		box.init(_world.get(), glm::vec2(xDist(randomGen), yDist(randomGen)), glm::vec2(1.0f, 1.0f), tex);
		_boxes.push_back(box);
	}

	_player.humanInit(_world.get(), glm::vec2(0.0f, -5.0f), glm::vec2(1.0f, 1.9f), glm::vec2(10, 1), "Textures/ss_player_base.png");
	_player.addWeapon(new AK47(_player.getPosition(), glm::vec2(1.0f, -0.75f)));
	_player.addWeapon(new AK47(_player.getPosition(), glm::vec2(2.2f, 1.55f), glm::vec2(1.0f, -0.75f)));
	_humans.push_back(&_player);

	Level::loadTiles("TestLevel_tiles.txt", "Textures/Tiles/test.png", _tiles);
	//Level::loadLevel("TestLevel.txt", _world.get(), _player, _humans, _boxes, _ground);

	Panel* panel = new Panel(glm::vec2(-0.95f, -0.95f), glm::vec2(0.4f, 1.8f), "Textures/GUI/panel.png", Color(255, 255, 255, 255));
	_guis.push_back(panel);

	Button* button = new Button(panel, glm::vec2(0.1f, 0.87f), glm::vec2(0.1f, 0.07f), "Textures/GUI/button.png", Color(255, 255, 255, 255));
	button->subscribeEvent(printWorking);
	_guis.push_back(button);

	Button* button1 = new Button(panel, glm::vec2(0.6f, 0.87f), glm::vec2(0.1f, 0.07f), "Textures/GUI/button.png", Color(255, 255, 255, 255));
	button1->subscribeEvent(printHello);
	_guis.push_back(button1);

	_staticShader.init("Shaders/staticShader.vert", "Shaders/staticShader.frag");
	_staticShader.bindAttributes();
	
	//_guiShader.init("Shaders/guiShader.vert", "Shaders/guiShader.frag");
	//_guiShader.bindAttributes();
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

	//Other
	if (_inputManager.isKeyDown(SDLK_F1)) {
		Level::saveLevel("TestLevel.txt", _player, _humans, _boxes, _ground);
	}

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
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	_staticShader.start();
	_staticShader.getUniformLocations();
	_staticShader.loadPMatrix(_camera.getCameraMatrix());
	_staticShader.loadTexture();

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

	//GUIS
	//_guiShader.start();
	//_guiShader.getUniformLocations();
	//_guiShader.loadTexture();

	//_guiBatch.begin();

	//for (int i = 0; i < _guis.size(); i++) {
	//	_guis[i].render(_guiBatch);	//< TODO: Make follow camera at all times
	//}

	//_guiBatch.end();
	//_guiBatch.renderBatch();


	//_guiShader.stop();

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

void printWorking()
{
	printf("Working\n");
}

void printHello()
{
	printf("Hello\n");
}