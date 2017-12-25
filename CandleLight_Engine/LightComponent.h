#pragma once

#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "GameObject.h"

#include <string>

class LightComponent : public RenderComponent
{
public:
	LightComponent()
	{
		this->color = Color(255, 255, 255, 255);
		_texture = ResourceManager::loadTexture("..\\CandleLight_Engine\\Textures\\light.png");
	}

	LightComponent(Color& color)
	{
		this->color = color;
		this->_texture = ResourceManager::loadTexture("..\\CandleLight_Engine\\Textures\\light.png");
	}

	LightComponent(Color& color, const std::string& texturePath)
	{
		this->color = color;
		_texture = ResourceManager::loadTexture(texturePath);
	}

	~LightComponent() {}

	virtual void update() override {}

	virtual void render(SpriteBatch& lightBatch) override
	{
		glm::vec2 pos = parent->transform.position;
		glm::vec2 size = parent->transform.scale;
		glm::vec4 destRect(pos.x - size.x / 2.0f, pos.y - size.y / 2.0f, size.x, size.y);
		lightBatch.addToBatch(destRect, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), 0.0f, _texture.id, color);
	}

	virtual std::string getID() override { return "light"; }

	Color color;

private:
	Texture _texture;
};