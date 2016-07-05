#pragma once

#include <string>
#include <vector>

#include <Box2D\Box2D.h>

#include "Player.h"
#include "Human.h"
#include "Box.h"

class Level
{
public:
	Level();
	~Level();

	static bool saveLevel(const std::string name, const Player& player, const std::vector<Human*>& humans, const std::vector<Box>& boxes);
	static bool loadLevel(const std::string name, b2World* world, Player& player, std::vector<Human*>& humans, std::vector<Box>& boxes);
};

