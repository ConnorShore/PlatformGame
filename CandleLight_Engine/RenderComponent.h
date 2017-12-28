#pragma once

#include "Component.h"
#include "SpriteBatch.h";

class RenderComponent : public Component
{
public:
	RenderComponent(){}
	~RenderComponent(){}

	virtual void update() override {}
	virtual void render(SpriteBatch& spriteBatch) = 0;

	virtual std::string getID() = 0
	{
		return "renderable";
	};
};