#include "MainGame.h"

#include <CandleLight_Engine\ResourceManager.h>

#include <SDL\SDL.h>
#include <GL\glew.h>
#include <random>

#include "AK47.h"
#include "Level.h"

MainGame::MainGame()
{
	//Bind light texture to fbo
	//Render scene
}

MainGame::~MainGame()
{
}

void MainGame::init()
{
	_window.createWindow("Platform Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight);
	_currentState = GameState::PLAY;
	_gameControl = GameControl::GAME;

	b2Vec2 gravity(0, -30.0f);
	_world = std::make_unique<b2World>(gravity);
	_world.get()->SetContactListener(&_collisionManager);

	_lightFBuffer.createFrameBuffer();
	_lightMap.id = _lightFBuffer.addTextureAttachment(_screenWidth, _screenHeight, 0);
	_lightFBuffer.unbindBuffer();

	_lightTex = ResourceManager::loadTexture("Textures/light.png");

	_camera.init(_screenWidth, _screenHeight);
	_camera.setScale(65.0f);

	_staticShader.init("Shaders/staticShader.vert", "Shaders/staticShader.frag");
	_staticShader.bindAttributes();

	_lightShader.init("Shaders/lightShader.vert", "Shaders/lightShader.frag");
	_lightShader.bindAttributes();

	_tileBatch.init();
	_spriteBatch.init();
	_guiBatch.init();
	_backgroundBatch.init();
	_lightBatch.init();
	
	//TODO: Make GUI pos based on GL coords nad dimensions based on world coords
	TiledPanel* inventory = new TiledPanel(_camera.pixelToGL(glm::vec2(-720, -720)), _camera.pixelToGL(glm::vec2(1440, 1440)), "Textures/GUI/panel.png", Color(255, 255, 255, 255), _camera.pixelToGL(glm::vec2(144)));
	_guis.push_back(inventory);
	for (int i = 0; i < 34; i++) {
		Icon* icon = new Icon("Textures/GUI/icon.png");
		inventory->addTile(*icon);
		_guis.push_back(icon);
	}

	//Background back1;
	//back1.init("Textures/Mountains/sky.png", glm::vec2(-22.0f), glm::vec2(100, 25), 0, 5);
	//back1.setAlpha(100);
	//_backgrounds.push_back(back1);
	//Background back2;
	//back2.init("Textures/Mountains/mountains_back.png", glm::vec2(-22.0f), glm::vec2(100, 25), 1, 5);
	//back2.setAlpha(100);
	//_backgrounds.push_back(back2);
	//Background back3;
	//back3.init("Textures/Mountains/mountains_front.png", glm::vec2(-22.0f), glm::vec2(100, 25), 2, 5);
	//back3.setAlpha(100);
	//_backgrounds.push_back(back3);

	Texture tex = ResourceManager::loadTexture("Textures/boxTex.png");

	_player.humanInit(_world.get(), glm::vec2(0.0f, -8.0f), glm::vec2(1.0f, 1.9f), glm::vec2(10, 1), "Textures/ss_player_base.png");
	_player.addWeapon(new AK47(_player.getPosition(), glm::vec2(1.0f, -0.75f)));
	_player.addWeapon(new AK47(_player.getPosition(), glm::vec2(2.2f, 1.55f), glm::vec2(1.0f, -0.75f)));
	_humans.push_back(&_player);

	Level::loadLevel("level1.txt", _world.get(), _tiles, _ground, _boxes, _lights);
	_ground.init(_world.get(), _ground.getVertices().size());


	//Light light1;
	//light1.color = Color(255, 0, 255, 255);
	//light1.position = glm::vec2(14, - 20.75);
	//light1.size = 12.0f;
	//_lights.push_back(light1);

	//light1.color = Color(255, 0, 0, 255);
	//light1.position = glm::vec2(40, -20);
	//light1.size = 14.0f;
	//_lights.push_back(light1);

	//light1.color = Color(255, 255, 0, 255);
	//light1.position = glm::vec2(22, -20);
	//light1.size = 5.0f;
	//_lights.push_back(light1);

	//light1.color = Color(255, 255, 255, 255);
	//light1.position = glm::vec2(30, -23);
	//light1.size = 10.0f;
	//_lights.push_back(light1);

	//light.color = Color(255, 255, 255, 255);
	//light.position = _player.getPosition();
	//light.size = 10.0f;
	//_lights.push_back(light);
}

void MainGame::input()
{
	_inputManager.update();

	//Check button input
	for (int i = 0; i < _guis.size(); i++) {
		if (!_guis[i]->isVisible()) break;
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
					case ICON:
						Icon* icon;
						icon = static_cast<Icon*>(_guis[i]);
						if (icon->inBox(pos)) printf("in box\n");
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

	light.position = _player.getPosition();

	if (_inputManager.isKeyDown(SDLK_e)) {
		_camera.setScale(_camera.getScale() + 0.25f);
	}

	if (_inputManager.isKeyDown(SDLK_q)) {
		_camera.setScale(_camera.getScale() - 0.25f);
	}

	if (_inputManager.isKeyDown(SDLK_i)) {
		if (_guis[0]->isVisible()) {
			for (int i = 0; i < _guis.size(); i++)
				_guis[i]->setVisible(false);
		}
		else {
			for (int i = 0; i < _guis.size(); i++)
				_guis[i]->setVisible(true);
		}
		_inputManager.keyReleased(SDLK_i);
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

	_camera.setPosition(glm::vec2(_player.getPosition().x + _player.getDimension().x / 2.0f, (_player.getPosition().y + _player.getDimension().y / 2.0f) + 2.0f));
	_camera.update();

	for (auto& back : _backgrounds)
		back.update(_camera.getPosition());

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

void MainGame::renderGeometry()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_staticShader.start();
	_staticShader.getUniformLocations();
	_staticShader.loadPMatrix(_camera.getCameraMatrix());
	_staticShader.loadResolution(glm::vec2(_screenWidth, _screenHeight));
	_staticShader.loadTexture();
	_staticShader.loadAmbient(glm::vec4(1.0f, 1.0f, 1.0f, 0.25f));

	//Backgrounds
	_backgroundBatch.begin(SortType::BACK_TO_FRONT);

	for (auto& back : _backgrounds)
		back.render(_backgroundBatch);

	_backgroundBatch.end();
	_backgroundBatch.renderBatch();

	//Bind lightmap
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, _lightMap.id);

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

	for (int i = 0; i < _boxes.size(); i++)
		_boxes[i].render(_spriteBatch);

	_spriteBatch.end();
	_spriteBatch.renderBatch();

	//unbind lightmap to not effect backgrounds
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);

	_staticShader.loadAmbient(glm::vec4(1.0f));
	_staticShader.loadPMatrix(_camera.getTransformationMatrix());

	_guiBatch.begin();

	for (auto& gui : _guis) {
		if(gui->isVisible())
			gui->render(_guiBatch);
	}
	
	_guiBatch.end();
	_guiBatch.renderBatch();

	_staticShader.stop();
}

void MainGame::renderLights()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBlendFunc(GL_ONE, GL_ONE);

	_lightShader.start();
	_lightShader.getUniformLocations();
	_lightShader.loadPMatrix(_camera.getCameraMatrix());
	_lightShader.loadTextures();

	_lightBatch.begin();

	for (auto& light : _lights) {
		light.render(_lightBatch);
	}
	//light.render(_lightBatch);

	_lightBatch.end();
	_lightBatch.renderBatch();

	_lightShader.stop();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void MainGame::render()
{
	_lightFBuffer.bindBuffer();
	renderLights();
	_lightFBuffer.unbindBuffer();

	renderGeometry();

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