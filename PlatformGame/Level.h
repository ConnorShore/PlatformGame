#pragma once

#include <string>
#include <vector>

#include <Box2D\Box2D.h>

#include "Player.h"
#include "Human.h"
#include "Box.h"
#include "Ground.h"
#include "Tile.h"

class Level
{
public:
	Level();
	~Level();

	static bool saveEditorLevel(const std::string& name, Ground& ground, const std::vector<Box>& boxes);

	static bool loadLevel(const std::string& name, b2World* world, std::vector<Tile>& tiles, Ground& ground, std::vector<Box>& boxes);

	static bool saveTiles(const std::string& name, const std::string& tileSheet, std::vector<Tile>& tiles);

	static bool loadTiles(const std::string& name, const std::string& tileSheet, std::vector<Tile>& tiles);

	static bool saveHumans(const std::string& name, const Player& player, const std::vector<Human*>& humans);
	static bool loadHumans(const std::string & name, b2World* world, Player & player, std::vector<Human*>& humans);

private:
	static void saveObjects(std::ofstream& level, const std::vector<Box>& boxes);
	static void saveGround(std::ofstream& level, Ground& ground);
};

