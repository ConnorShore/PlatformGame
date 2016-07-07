#pragma once

#include <vector>

#include "Agent.h"
#include "Weapon.h"
#include "Damagable.h"

class Weapon;

//Break up Agent to be abstract and have lower levels such as human, bug, etc.

class Human : public Agent, public Damagable
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
	Weapon* getPrimaryWeapon() const { return _primaryWeapon; }
	Weapon* getSecondaryWeapon() const { return _secondaryWeapon; }

	bool canShoot() const { return _canShoot; }
	bool isShooting() const { return _shooting; }
	bool isPlayer() const { return _isPlayer; }
	float getHealth() const { return _damageStats->health; }

	void setHealth(float newHealth) { _damageStats->health = newHealth; }

protected:
	Damagable* _damageStats = new Damagable;
	bool _isAlive = true;
	bool _onGround = false;	//< Add world collision (manifold) to determine
	bool _canJump = false;
	bool _canShoot = true;
	bool _shooting = false;
	bool _isPlayer = false;

	std::vector<Weapon*> _weapons;
	Weapon* _currentWeapon;
	Weapon* _primaryWeapon;
	Weapon* _secondaryWeapon;

	void jump();
};