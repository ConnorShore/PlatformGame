#pragma once

#include <string>

#include "Agent.h"
#include "Texture.h"

enum class FireType {NONE, SINGLE, BURST, AUTO};

class Weapon
{
public:
	Weapon(Agent& parent, FireType& fireType, const Texture& weapon, const std::string& name);
	Weapon(){}
	~Weapon();

	virtual void update();
	virtual void render();

protected:
	Agent _parent;
	FireType _fireMode;
	Texture _weapon;
	std::string _name;
};

