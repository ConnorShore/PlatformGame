#include "RenderSystem.h"
#include "GameObjectManager.h"
#include "Components.h"


RenderSystem::RenderSystem()
{
}

RenderSystem::~RenderSystem()
{
}

void RenderSystem::init(Camera& camera)
{
	_camera = &camera;

	_lightFBuffer.createFrameBuffer();
	_lightMap.id = _lightFBuffer.addTextureAttachment(_camera->getScreenWidth(), _camera->getScreenHeight(), 0);
	_lightFBuffer.unbindBuffer();

	_staticShader.init("..\\CandleLight_Engine\\Shaders\\staticShader.vert", "..\\CandleLight_Engine\\Shaders\\staticShader.frag");
	_staticShader.bindAttributes();

	_lightShader.init("..\\CandleLight_Engine\\Shaders\\lightShader.vert", "..\\CandleLight_Engine\\Shaders\\lightShader.frag");
	_lightShader.bindAttributes();

	_spriteBatch.init();
	_lightBatch.init();
}

void RenderSystem::prepare()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderSystem::render()
{
	//TODO: Extract out components so dont have to do it later (optimization)
	std::vector<GameObject*> objects = GameObjectManager::instance().getGameObjects();
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->hasComponent("sprite")) {
			sprites.push_back(objects[i]);
		}
		else if (objects[i]->hasComponent("light")) {
			lights.push_back(objects[i]);
		}
	}

	_lightFBuffer.bindBuffer();
	renderLights();
	_lightFBuffer.unbindBuffer();
	
	renderGeometry();

	sprites.clear();
	lights.clear();
}

void RenderSystem::renderGeometry()
{
	prepare();

	_staticShader.start();
	_staticShader.getUniformLocations();
	_staticShader.loadPMatrix(_camera->getCameraMatrix());
	_staticShader.loadResolution(glm::vec2(_camera->getScreenWidth(), _camera->getScreenHeight()));
	_staticShader.loadTexture();
	_staticShader.loadAmbient(glm::vec4(0.35f));

	//Bind lightmap
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, _lightMap.id);

	_spriteBatch.begin();

	for (int i = 0; i < sprites.size(); i++) {
		SpriteComponent* sprite = static_cast<SpriteComponent*>(sprites[i]->getComponent("sprite"));
		sprite->render(_spriteBatch);
	}

	_spriteBatch.end();
	_spriteBatch.renderBatch();

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);

	_staticShader.stop();
}

void RenderSystem::renderLights()
{
	prepare();
	glBlendFunc(GL_ONE, GL_ONE);

	_lightShader.start();
	_lightShader.getUniformLocations();
	_lightShader.loadPMatrix(_camera->getCameraMatrix());
	_lightShader.loadTextures();

	_lightBatch.begin();

	for (int i = 0; i < lights.size(); i++) {
		LightComponent* lightComp = static_cast<LightComponent*>(lights[i]->getComponent("light"));
		lightComp->render(_lightBatch);
	}

	_lightBatch.end();
	_lightBatch.renderBatch();

	_lightShader.stop();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
