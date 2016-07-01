#pragma once

#include <Box2D\Box2D.h>
#include <string>
#include <vector>
#include <iostream>

#include "Damagable.h"

enum CollisionCategory
{
	CATEGORY_ENVIRONMENT = 0x0001,
	CATEGORY_FRIENDLY = 0x0002,
	CATEGORY_ENEMY = 0x0004,
	CATEGORY_NEUTRAL = 0x0008
};

enum CollisionMask
{
	MASK_ALL = CATEGORY_ENVIRONMENT | CATEGORY_FRIENDLY | CATEGORY_ENEMY | CATEGORY_NEUTRAL,
	MASK_FRIENDLY = CATEGORY_ENVIRONMENT | CATEGORY_ENEMY | CATEGORY_NEUTRAL,
	MASK_ENEMY = CATEGORY_ENVIRONMENT | CATEGORY_FRIENDLY | CATEGORY_NEUTRAL
};

class CollisionManager : public b2ContactListener
{
public:
	std::vector<b2Body*> bodiesToDestroy;

	void BeginContact(b2Contact* contact)
	{
		b2Body* bodyA = contact->GetFixtureA()->GetBody();
		b2Body* bodyB= contact->GetFixtureB()->GetBody();

		Damagable* bodyAName = (Damagable*)(bodyA->GetUserData());
		Damagable* bodyBName = (Damagable*)(bodyB->GetUserData());

		if (bodyAName != NULL && bodyBName != NULL) {
			if (bodyAName->name == "box" && bodyBName->name == "bullet") {
				bodyAName->health -= bodyBName->damage;
				bodyBName->health = 0.0f;
			}	
		}
	}

	void EndContact(b2Contact* contact)
	{
		
	}
};