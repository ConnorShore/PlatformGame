#include "EditorScreen.h"



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

	_tileBatch.init();
	_spriteBatch.init();

	_staticShader.init("Shaders/staticShader.vert", "Shaders/staticShader.frag");
	_staticShader.bindAttributes();
}

void EditorScreen::input()
{
	_inputManager.update();
}

void EditorScreen::update()
{
	_camera.update();
}

void EditorScreen::render()
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
}

void EditorScreen::run()
{
	init();
	gameLoop();
	cleanUp();
}