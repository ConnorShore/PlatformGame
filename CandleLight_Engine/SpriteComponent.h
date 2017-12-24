#pragma once

#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "GameObject.h"

#include <string>

class SpriteComponent : public RenderComponent
{
public:
	SpriteComponent(const std::string texturePath) 
	{
		_texture = ResourceManager::loadTexture(texturePath);
	}

	SpriteComponent() {}

	virtual void update() override {}

	virtual void render(SpriteBatch& spriteBatch) override 
	{
		if (parent != nullptr) {
			glm::vec4 destRect(parent->transform.position, parent->transform.scale);
			glm::vec4 destUV(0.0f, 0.0f, 1.0f, 1.0f);
			spriteBatch.addToBatch(destRect, destUV, 1.0f, _texture.id, Color(255, 0, 0, 255));
		}
	}

	virtual std::string getID() override { return "sprite"; }

private:
	Texture _texture;
};