#include "EditorScreen.h"

#include <CandleLight_Engine\ResourceManager.h>
#include "Level.h"


EditorScreen::EditorScreen() : _isRunning(true)
{
}


EditorScreen::~EditorScreen()
{
}

void EditorScreen::init()
{
	_window.createWindow("Level Editor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight);
	_camera.init(_screenWidth, _screenHeight);
	_camera.setScale(30.0f);

	b2Vec2 gravity(0, -20.0f);
	_world = std::make_unique<b2World>(gravity);

	_sheetTex = ResourceManager::loadTexture("Textures/Tiles/test.png");

	_tileBatch.init();
	_spriteBatch.init();

	_staticShader.init("Shaders/staticShader.vert", "Shaders/staticShader.frag");
	_staticShader.bindAttributes();
}

void EditorScreen::input()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_QUIT:
			_isRunning = false;
			break;
		case SDL_KEYDOWN:
			_inputManager.keyPressed(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			_inputManager.keyReleased(evnt.key.keysym.sym);
			break;
		case SDL_MOUSEWHEEL:
			updateMouseWheel(evnt);
		case SDL_MOUSEMOTION:
			_inputManager.setMousePos(evnt.motion.x, evnt.motion.y);
			break;
		case SDL_MOUSEBUTTONDOWN:
			updateMouseDown(evnt);
			break;
		//case SDL_MOUSEBUTTONUP:
		//	updateMouseUp(evnt);
		//	break;
		}
	}
}

void EditorScreen::update()
{
	_camera.update();
}

void EditorScreen::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

	for (int i = 0; i < _boxes.size(); i++)
		_boxes[i].render(_spriteBatch);

	_spriteBatch.end();
	_spriteBatch.renderBatch();

	_staticShader.stop();

	_window.swapWindow();
}

void EditorScreen::gameLoop()
{
	_timer.TimeInit();

	while (_isRunning != false) {
		_timer.FpsLimitInit();
		_timer.calcDeltaTime();

		update();
		input();
		render();

		_timer.LimitFPS(60.0f);
		_timer.CalculateFPS(false);
	}
}

void EditorScreen::cleanUp()
{
	_window.destroyWindow();
	SDL_Quit();
	exit(0);
}

void EditorScreen::run()
{
	init();
	gameLoop();
	cleanUp();
}

void EditorScreen::updateMouseDown(const SDL_Event& evnt)
{
	switch (evnt.button.button) {
	case SDL_BUTTON_LEFT:
		_mouseButtons[LEFT_BUTTON] = true;
		if (_selectMode == SelectMode::PLACE) {
			glm::vec2 pos = glm::vec2(_camera.screenToWorldCoords(glm::vec2(evnt.button.x, evnt.button.y)));

			switch (_objectMode) {
			case ObjectMode::TILE:
				pos.x = glm::floor(pos.x / TILE_SIZE) * TILE_SIZE;
				pos.y = glm::floor(pos.y / TILE_SIZE) * TILE_SIZE;
				_tiles.emplace_back(pos, _currentTileIndex, _sheetTex);	//Add array of 64 elements for index, and use mouse scroller to cycle through the different indexes
				break;
			case ObjectMode::BOX:
				Texture boxTex = ResourceManager::loadTexture("Textures/boxTex.png");
				Box box;
				box.init(_world.get(), pos, glm::vec2(1.0f), boxTex, 1.0f);
				_boxes.push_back(box);
				break;
			}
		}
		else {
			//Select Mode
			
		}

		break;
	case SDL_BUTTON_RIGHT:
		_mouseButtons[RIGHT_BUTTON] = true;
		glm::vec2 pos = glm::vec2(_camera.screenToWorldCoords(glm::vec2(evnt.button.x, evnt.button.y)));
		for (int i = 0; i < _tiles.size(); i++) {
			if (pos.x > _tiles[i].getPosition().x && pos.y > _tiles[i].getPosition().y
				&& pos.x <= _tiles[i].getPosition().x + TILE_SIZE && pos.y <= _tiles[i].getPosition().y + TILE_SIZE) {
				_tiles[i] = _tiles.back();
				_tiles.pop_back();
				i--;
			}
		}
		break;
	}
}

void EditorScreen::updateMouseWheel(const SDL_Event & evnt)
{
	if (_selectMode == SelectMode::PLACE) {
		switch (_objectMode) {
		case ObjectMode::TILE:
			if (evnt.wheel.y > 0.0f) {
				if (_currentTileIndex < 63) _currentTileIndex++;
			}
			else {
				if (_currentTileIndex > 0) _currentTileIndex--;
			}
			printf("%d\n", _currentTileIndex);
		}
	}
}
