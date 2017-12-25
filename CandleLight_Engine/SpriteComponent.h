#pragma once

#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "GameObject.h"

#include <string>

class SpriteComponent : public RenderComponent
{
public:
	SpriteComponent(const std::string& texturePath) 
	{
		_texture = ResourceManager::loadTexture(texturePath);
		uvRect = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
		color = Color(255, 255, 255, 255);
		depth = 0.0f;
	}

	SpriteComponent() {}

	virtual void update() override {}

	virtual void render(SpriteBatch& spriteBatch) override 
	{
		if (parent != nullptr) {
			glm::vec4 destRect(parent->transform.position, parent->transform.scale);
			spriteBatch.addToBatch(destRect, uvRect, depth, _texture.id, color);
		}
	}

	virtual std::string getID() override { return "sprite"; }

	glm::vec4 uvRect;
	Color color;
	float depth;

private:
	Texture _texture;
};