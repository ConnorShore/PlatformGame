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
	_camera.setScale(65.0f);

	b2Vec2 gravity(0.0f, 0.0f);
	_world = std::make_unique<b2World>(gravity);

	_sheetTex = ResourceManager::loadTexture("Textures/Tiles/mountains.png");
	_nodeTex = ResourceManager::loadTexture("Textures/Editor/node.png");
	_playerTex = ResourceManager::loadTexture("Textures/Editor/playerTex.png");

	_tileBatch.init();
	_spriteBatch.init();
	_guiBatch.init();
	_hudBatch.init();	
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

	Panel* panel = new Panel(glm::vec2(-0.98f, -0.98f), glm::vec2(0.45f, 1.95f), "Textures/GUI/panel.png", Color(255, 255, 255, 150));
	_guis.push_back(panel);
	
	RadioButton* radio = new RadioButton(panel, glm::vec2(0.25f, 0.87f), "Textures/GUI/radio_button.png", Color(255, 255, 255, 255));
	radio->setSelected(false);
	radio->subscribeEvent(this, &EditorScreen::switchSelectMode, SelectMode::SELECT);
	_guis.push_back(radio);
	_guiLabels.emplace_back(radio, "Select", 1.0f, Color(0, 0, 0, 255));

	RadioButton* radio1 = new RadioButton(panel, glm::vec2(0.65f, 0.87f), "Textures/GUI/radio_button.png", Color(255, 255, 255, 255));
	radio1->setSelected(true);
	radio1->subscribeEvent(this, &EditorScreen::switchSelectMode, SelectMode::PLACE);
	_guis.push_back(radio1);
	_guiLabels.emplace_back(radio1, "Place", 1.0f, Color(0,0,0,255));

	Button* button = new Button(panel, glm::vec2(0.30f, 0.74f), glm::vec2(0.15f, 0.1f), "Textures/GUI/button.png", Color(255, 255, 255, 200));
	button->subscribeEvent(this, &EditorScreen::clear);
	button->setEnabled(true);
	_guis.push_back(button);
	_guiLabels.emplace_back(button, "Clear", 1.0f, Color(100,100,100,255), LabelPosition::CENTER);

	Checkbox* background = new Checkbox(panel, glm::vec2(0.25f, 0.6f), "Textures/GUI/radio_button.png", Color(255, 255, 255, 255));
	background->setSelected(true);
	background->subscribeEvent(this, &EditorScreen::toggleBackground);
	_guis.push_back(background);
	_guiLabels.emplace_back(background, "Background", 0.65f, Color(0, 0, 0, 255));

	Checkbox* gridMove = new Checkbox(panel, glm::vec2(0.5f, 0.6f), "Textures/GUI/radio_button.png", Color(255, 255, 255, 255));
	gridMove->setSelected(true);
	gridMove->subscribeEvent(this, &EditorScreen::toggleGridSnap);
	_guis.push_back(gridMove);
	_guiLabels.emplace_back(gridMove, "Snap Grid", 0.65f, Color(0, 0, 0, 255));

	Checkbox* drag = new Checkbox(panel, glm::vec2(0.75f, 0.6f), "Textures/GUI/radio_button.png", Color(255, 255, 255, 255));
	drag->setSelected(true);
	drag->subscribeEvent(this, &EditorScreen::toggleDrag);
	_guis.push_back(drag);
	_guiLabels.emplace_back(drag, "Drag", 0.65f, Color(0, 0, 0, 255));

	RadioButton* ground = new RadioButton(panel, glm::vec2(0.25f, 0.45f), "Textures/GUI/radio_button.png", Color(255, 255, 255, 255));
	ground->setGroup(1);
	ground->setSelected(false);
	ground->subscribeEvent(this, &EditorScreen::switchObjectMode, ObjectMode::GROUND);
	_guis.push_back(ground);
	_guiLabels.emplace_back(ground, "Ground", 1.0f, Color(0, 0, 0, 255));

	RadioButton* tile = new RadioButton(panel, glm::vec2(0.5f, 0.45f), "Textures/GUI/radio_button.png", Color(255, 255, 255, 255));
	tile->setGroup(1);
	tile->setSelected(true);
	tile->subscribeEvent(this, &EditorScreen::switchObjectMode, ObjectMode::TILE);
	_guis.push_back(tile);
	_guiLabels.emplace_back(tile, "Tile", 1.0f, Color(0, 0, 0, 255));

	RadioButton* box = new RadioButton(panel, glm::vec2(0.75f, 0.45f), "Textures/GUI/radio_button.png", Color(255, 255, 255, 255));
	box->setGroup(1);
	box->setSelected(false);
	box->subscribeEvent(this, &EditorScreen::switchObjectMode, ObjectMode::BOX);
	_guis.push_back(box);
	_guiLabels.emplace_back(box, "Box", 1.0f, Color(0, 0, 0, 255));

	Button* save = new Button(panel, glm::vec2(0.30f, 0.25f), glm::vec2(0.15f, 0.1f), "Textures/GUI/button.png", Color(255, 255, 255, 200));
	save->subscribeEvent(this, &EditorScreen::saveLevel, "level1.txt", "Textures/Tiles/mountains.png");
	save->setEnabled(true);
	_guis.push_back(save);
	_guiLabels.emplace_back(save, "Save", 1.0f, Color(100, 100, 100, 255), LabelPosition::CENTER);

	_spriteFont = new SpriteFont("Fonts/BEBAS.ttf", 32);

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
				case CHECKBOX:
					Checkbox* check;
					check = static_cast<Checkbox*>(_guis[i]);
					check->onClick();
					_inputManager.keyReleased(SDL_BUTTON_LEFT);
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

	if (_inputManager.isKeyDown(SDLK_ESCAPE)) {
		_isRunning = false;
	}

	if (_inputManager.isKeyDown(SDLK_e)) {
		_camera.setScale(_camera.getScale() + 0.1f);
	}

	if (_inputManager.isKeyDown(SDLK_q)) {
		_camera.setScale(_camera.getScale() - 0.1f);
	}

	//MoveCamera
	float CAM_SPEED = 0.25f;
	if (_inputManager.isKeyDown(SDLK_LSHIFT)) CAM_SPEED = 0.75f;

	if (_inputManager.isKeyDown(SDLK_s)) {
		_camera.setPosition(_camera.getPosition() - glm::vec2(0.0f, CAM_SPEED));
	}
	else if (_inputManager.isKeyDown(SDLK_w)) {
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, CAM_SPEED));
	}
	if (_inputManager.isKeyDown(SDLK_d)) {
		_camera.setPosition(_camera.getPosition() + glm::vec2(CAM_SPEED, 0.0f));
	}
	else if (_inputManager.isKeyDown(SDLK_a)) {
		_camera.setPosition(_camera.getPosition() - glm::vec2(CAM_SPEED, 0.0f));
	}

	updateGUI();

	if(!_drag)
		_inputManager.keyReleased(SDL_BUTTON_LEFT);
}

void EditorScreen::update()
{
	_camera.update();	
	
	if (_showBackgrounds) {
		for (auto& back : _backgrounds)
			back.update(_camera.getPosition());
	}

	_world->Step(1 / 60.0f, 0, 0);
}

void EditorScreen::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_staticShader.start();
	_staticShader.getUniformLocations();
	_staticShader.loadPMatrix(_camera.getCameraMatrix());
	_staticShader.loadTexture();

	//Backgrounds
	if (_showBackgrounds) {
		_backgroundBatch.begin(SortType::BACK_TO_FRONT);

		for (auto& back : _backgrounds)
			back.render(_backgroundBatch);

		_backgroundBatch.end();
		_backgroundBatch.renderBatch();
	}

	//Tiles
	_tileBatch.begin();

	for (int i = 0; i < _tiles.size(); i++) {
		_tiles[i].render(_tileBatch);
	}

	for (auto& vert : _ground.getVertices()) {
		float size = 0.25f;
		glm::vec4 destRect(vert.x - size/2, vert.y - size/2, size, size);
		_tileBatch.addToBatch(destRect, glm::vec4(0, 0, 1, 1), 1.0f, _nodeTex.id, Color(255, 255, 255, 255));
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
		_guis[i]->render(_guiBatch);
	}

	_guiBatch.end();
	_guiBatch.renderBatch();

	//Font
	_hudBatch.begin();

	for (int i = 0; i < _guiLabels.size(); i++) {
		_guiLabels[i].render(_hudBatch, _camera);
	}

	_hudBatch.end();
	_hudBatch.renderBatch();

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
		_mouseButtons[RIGHT_BUTTON] = false;

		if (_selectMode == SelectMode::PLACE) {
			Texture tex;
			switch (_objectMode) {
			case ObjectMode::GROUND:
				_ground.addVertex(pos);
				break;
			case ObjectMode::TILE:
				if (_gridSnap) {
					pos.x = glm::floor(pos.x / TILE_SIZE) * TILE_SIZE;
					pos.y = glm::floor(pos.y / TILE_SIZE) * TILE_SIZE;
				} else {
					pos.x -= TILE_SIZE / 2.0f;
					pos.y -= TILE_SIZE / 2.0f;
				}

				_tiles.emplace_back(pos, _currentTileIndex, _sheetTex);
				break;
			case ObjectMode::BOX:
				tex = ResourceManager::loadTexture("Textures/boxTex.png");
				Box box;
				box.init(_world.get(), pos, glm::vec2(1.0f), tex, 1.0f);
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
		_mouseButtons[LEFT_BUTTON] = false;

		pos = _camera.screenToWorldCoords(_inputManager.getMousePos());

		if (_selectMode == SelectMode::PLACE) {
			switch (_objectMode) {
			case ObjectMode::GROUND:
				float nodeSize;
				nodeSize = 0.25f;
				for (int i = 0; i < _ground.getVertices().size(); i++) {
					glm::vec2 vert = _ground.getVertices()[i];
					if (pos.x > vert.x - nodeSize/2 && pos.y > vert.y - nodeSize/2
						&& pos.x <= vert.x + nodeSize/2 && pos.y <= vert.y + nodeSize/2) {
						_ground.getVertices()[i] = _ground.getVertices().back();
						_ground.getVertices().pop_back();
					}
				}
				break;
			case ObjectMode::TILE:
				for (int i = 0; i < _tiles.size(); i++) {
					if (pos.x > _tiles[i].getPosition().x && pos.y > _tiles[i].getPosition().y
						&& pos.x <= _tiles[i].getPosition().x + TILE_SIZE && pos.y <= _tiles[i].getPosition().y + TILE_SIZE) {
						_tiles[i] = _tiles.back();
						_tiles.pop_back();
					}
				}
				break;
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

void EditorScreen::switchObjectMode(ObjectMode & mode)
{
	_objectMode = mode;
}

void EditorScreen::toggleBackground()
{
	if (_showBackgrounds)
		_showBackgrounds = false;
	else
		_showBackgrounds = true;
}

void EditorScreen::toggleGridSnap()
{
	if (_gridSnap)
		_gridSnap = false;
	else
		_gridSnap = true;
}

void EditorScreen::toggleDrag()
{
	if (_drag)
		_drag = false;
	else
		_drag = true;
}

void EditorScreen::clear()
{
	_tiles.clear();
	_boxes.clear();
	_ground.getVertices().clear();
}

void EditorScreen::saveLevel(const std::string& fileName, const std::string& texSheet)
{

	Level::saveTiles(fileName, texSheet, _tiles);
	Level::saveEditorLevel(fileName, _ground, _boxes);
}
