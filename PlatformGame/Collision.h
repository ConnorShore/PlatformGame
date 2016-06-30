#pragma once

#include <Box2D\Box2D.h>
#include <string>
#include <vector>
#include <iostream>

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

		char* bodyAName = (char*)bodyA->GetUserData(); 
		char* bodyBName = (char*)bodyB->GetUserData();

		if (bodyAName != NULL && bodyBName != NULL) {
			if (bodyAName == "box" && bodyBName == "bullet") {
				bodiesToDestroy.push_back(bodyA);
				bodiesToDestroy.push_back(bodyB);
			}	
		}
	}

	void EndContact(b2Contact* contact)
	{
		
	}
};