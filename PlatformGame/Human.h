#pragma once

#include <vector>

#include "Agent.h"
#include "Weapon.h"

class Weapon;

//Break up Agent to be abstract and have lower levels such as human, bug, etc.

class Human : public Agent
{
public:
	Human();
	~Human();

	void agentInit(b2World* world, const glm::vec2& position, const glm::vec2& dimension, const glm::ivec2& sheetDims, const std::string& texPath);
	void agentUpdate(); //< Update will go in here, but use this to determine collision/onground/etc stuff
	void agentRender(SpriteBatch& spriteBatch);

	void addWeapon(Weapon* weapon);

	virtual void init() override {};
	virtual void update() override {}
	virtual void render() override {}

	virtual void shoot(const glm::vec2& direction) {}
	virtual glm::vec4 animate() { return glm::vec4(0, 0, 0, 0); };

protected:
	bool _onGround = false;	//< Add world collision (manifold) to determine
	bool _canJump = false;
	bool _canShoot = true;

	std::vector<Weapon*> _weapons;
	Weapon* _currentWeapon;
	Weapon* _primaryWeapon;
	Weapon* _secondaryWeapon;

	void jump();
};