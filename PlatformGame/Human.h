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

	void humanInit(b2World* world, const glm::vec2& position, const glm::vec2& dimension, const glm::ivec2& sheetDims, const std::string& texPath);
	void humanUpdate(); //< Update will go in here, but use this to determine collision/onground/etc stuff
	void humanRender(SpriteBatch& spriteBatch);

	void addWeapon(Weapon* weapon);

	virtual void init() override {};
	virtual void update() override {}
	virtual void render() override {}

	virtual glm::vec4 animate() { return glm::vec4(0, 0, 0, 0); };

	Weapon* getCurrentWeapon() const { return _currentWeapon; }

	bool canShoot() const { return _canShoot; }
	bool isShooting() const { return _shooting; }

protected:
	bool _onGround = false;	//< Add world collision (manifold) to determine
	bool _canJump = false;
	bool _canShoot = true;
	bool _shooting = false;

	std::vector<Weapon*> _weapons;
	Weapon* _currentWeapon;
	Weapon* _primaryWeapon;
	Weapon* _secondaryWeapon;

	void jump();
};