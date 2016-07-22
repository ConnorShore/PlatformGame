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
	_guiBatch.init();

	Panel* panel = new Panel(glm::vec2(-0.98f, -0.98f), glm::vec2(0.45f, 1.95f), "Textures/GUI/panel.png", Color(255, 255, 255, 150));
	_guis.push_back(panel);
	
	RadioButton* radio = new RadioButton(panel, glm::vec2(0.1f, 0.87f), "Textures/GUI/radio_button.png", Color(255, 255, 255, 200));
	radio->setSelected(false);
	radio->subscribeEvent(this, &EditorScreen::switchSelectMode, SelectMode::SELECT);
	_guis.push_back(radio);

	RadioButton* radio1 = new RadioButton(panel, glm::vec2(0.55f, 0.87f), "Textures/GUI/radio_button.png", Color(255, 255, 255, 200));
	radio1->setSelected(true);
	radio1->subscribeEvent(this, &EditorScreen::switchSelectMode, SelectMode::PLACE);
	_guis.push_back(radio1);

	Button* button = new Button(panel, glm::vec2(0.35f, 0.74f), glm::vec2(0.15f, 0.1f), "Textures/GUI/button.png", Color(255, 255, 255, 200));
	button->subscribeEvent(this, &EditorScreen::clear);
	_guis.push_back(button);

	_gridShader.init("Shaders/gridShader.vert", "Shaders/gridShader.frag");
	_gridShader.bindAttributes();

	_staticShader.init("Shaders/staticShader.vert", "Shaders/staticShader.frag");
	_staticShader.bindAttributes();
}

void EditorScreen::updateGUI()
{
	//Check button input
	for (int i = 0; i < _guis.size(); i++) {
		_guis[i]->update();

		glm::vec2 pos = _camera.screenToGLCoords(_inputManager.getMousePos());

		if (_guis[i]->inBox(pos))
			_guiControl = true;
		else if (_guis[i]->getParent() != nullptr && _guis[i]->getParent()->inBox(pos))
			_guiControl = true;
		else
			_guiControl = false;

		GUIType t = _guis[i]->getType();
		if (_guis[i]->inBox(pos)) {
			_guis[i]->setMouseOver(true);
			_guiControl = true;
			if (_inputManager.isKeyDown(SDL_BUTTON_LEFT)) {
				switch (t) {
				case BUTTON:
					Button* button;
					button = static_cast<Button*>(_guis[i]);
					button->onClick();
					break;
				case RADIO_BUTTON:
					RadioButton* radio;
					radio = static_cast<RadioButton*>(_guis[i]);
					radio->setSelected(true);
					break;
				case NONE:
					break;
				}
			}
		}
		else {
			_guis[i]->setMouseOver(false);
		}
	}
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
			_inputManager.keyPressed(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			_inputManager.keyReleased(evnt.button.button);
			//updateMouseUp(evnt);
			break;
		}
	}

	if (_inputManager.isKeyDown(SDL_BUTTON_LEFT) || _inputManager.isKeyDown(SDL_BUTTON_RIGHT)) {
		if (!_guiControl)
			updateMouseDown(evnt);
	}

	updateGUI();
}

void EditorScreen::update()
{
	_camera.update();

	_world->Step(1 / 60.0f, 0, 0);
}

void EditorScreen::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Grid

	//_gridShader.start();
	//_gridShader.getUniformLocations();
	//_gridShader.loadPMatrix(_camera.getCameraMatrix());

	//_gridShader.stop();

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

	//GUIs
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
	glm::vec2 pos = glm::vec2(_camera.screenToWorldCoords(glm::vec2(evnt.button.x, evnt.button.y)));

	switch (evnt.button.button) {
	case SDL_BUTTON_LEFT:
		_mouseButtons[LEFT_BUTTON] = true;

		if (_selectMode == SelectMode::PLACE) {
			switch (_objectMode) {
			case ObjectMode::TILE:
				pos.x = glm::floor(pos.x / TILE_SIZE) * TILE_SIZE;
				pos.y = glm::floor(pos.y / TILE_SIZE) * TILE_SIZE;
				_tiles.emplace_back(pos, _currentTileIndex, _sheetTex);
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

		if (_selectMode == SelectMode::PLACE) {
			pos = _camera.screenToWorldCoords(_inputManager.getMousePos());
			for (int i = 0; i < _tiles.size(); i++) {
				if (pos.x > _tiles[i].getPosition().x && pos.y > _tiles[i].getPosition().y
					&& pos.x <= _tiles[i].getPosition().x + TILE_SIZE && pos.y <= _tiles[i].getPosition().y + TILE_SIZE) {
					_tiles[i] = _tiles.back();
					_tiles.pop_back();
				}
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

void EditorScreen::switchSelectMode(SelectMode & mode)
{
	_selectMode = mode;
}

void EditorScreen::clear()
{
	_tiles.clear();
	_boxes.clear();
}