#pragma once

#include <string>
#include <vector>

#include <Box2D\Box2D.h>

#include "Player.h"
#include "Human.h"
#include "Box.h"
#include "Ground.h"

class Level
{
public:
	Level();
	~Level();

	static bool saveLevel(const std::string name, const Player& player, const std::vector<Human*>& humans, const std::vector<Box>& boxes, Ground& ground);
	static bool loadLevel(const std::string name, b2World* world, Player& player, std::vector<Human*>& humans, std::vector<Box>& boxes, Ground& ground);

private:
	static void saveHumans(std::ofstream& level, const Player& player, const std::vector<Human*>& humans);
	static void saveObjects(std::ofstream& level, const std::vector<Box>& boxes);
	static void saveGround(std::ofstream& level, Ground& ground);
};

