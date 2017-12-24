#include "RenderSystem.h"
#include "GameObjectManager.h"
#include "SpriteComponent.h"


RenderSystem::RenderSystem()
{
}

RenderSystem::~RenderSystem()
{
}

void RenderSystem::init()
{
	_staticShader.init("Shaders/staticShader.vert", "Shaders/staticShader.frag");
	_staticShader.bindAttributes();

	_spriteBatch.init();
}

void RenderSystem::prepare()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderSystem::render(Camera& camera)
{
	_staticShader.start();
	_staticShader.getUniformLocations();
	_staticShader.loadPMatrix(camera.getCameraMatrix());
	_staticShader.loadResolution(glm::vec2(1280, 720));
	_staticShader.loadTexture();
	_staticShader.loadAmbient(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	renderSprites();

	_staticShader.stop();
}

void RenderSystem::renderSprites()
{
	std::vector<GameObject*> objects = GameObjectManager::instance().getGameObjects();

	_spriteBatch.begin();

	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->hasComponent("sprite")) {
			SpriteComponent* sprite = static_cast<SpriteComponent*>(objects[i]->getComponent("sprite"));
			sprite->render(_spriteBatch);
		}
	}

	_spriteBatch.end();
	_spriteBatch.renderBatch();
}
