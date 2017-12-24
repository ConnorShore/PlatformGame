#pragma once

#include "StaticShader.h"
#include "SpriteBatch.h"
#include "Camera.h"

class RenderSystem
{
public:
	RenderSystem();
	~RenderSystem();

	void init();
	void prepare();
	void render(Camera& camera);
	
private:
	StaticShader _staticShader;
	SpriteBatch _spriteBatch;

	void renderSprites();
};

