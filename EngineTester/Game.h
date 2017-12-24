#pragma once

#include <CandleLight_Engine\Window.h>
#include <CandleLight_Engine\Timing.h>
#include <CandleLight_Engine\InputManager.h>
#include <CandleLight_Engine\Component.h>
#include <CandleLight_Engine\GameObjectManager.h>
#include <CandleLight_Engine\StaticShader.h>
#include <CandleLight_Engine\SpriteBatch.h>
#include <CandleLight_Engine\Camera.h>
#include <CandleLight_Engine\Texture.h>
#include <CandleLight_Engine\RenderSystem.h>

class Game
{
public:
	Game();
	~Game();

	void run();

private:
	Window _window;
	Timing _timer;
	InputManager _inputManager;
	StaticShader _staticShader;
	SpriteBatch _spriteBatch;
	Camera _camera;
	Texture tex;
	RenderSystem _renderSystem;

	bool _isRunning;

	void init();
	void input();
	void update();
	void render();
	void gameLoop();
	void cleanUp();
};

