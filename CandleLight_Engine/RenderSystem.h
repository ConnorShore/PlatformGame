#pragma once

#include "StaticShader.h"
#include "LightShader.h"
#include "SpriteBatch.h"
#include "Camera.h"
#include "FrameBuffer.h"
#include "Texture.h";
#include "GameObject.h"

#include <vector>

class RenderSystem
{
public:
	RenderSystem();
	~RenderSystem();

	void init(Camera& camera);
	void render();
	
private:
	StaticShader _staticShader;
	LightShader _lightShader;

	SpriteBatch _spriteBatch;
	SpriteBatch _lightBatch;

	FrameBuffer _lightFBuffer;
	Texture _lightMap;

	Camera* _camera;

	std::vector<GameObject*> sprites;
	std::vector<GameObject*> lights;

	void prepare();
	void renderGeometry();
	void renderLights();
};

