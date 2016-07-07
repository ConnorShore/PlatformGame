#include "Level.h"

#include <CandleLight_Engine\Texture.h>
#include <CandleLight_Engine\ResourceManager.h>

#include <fstream>
#include <glm\glm.hpp>
#include <string>

#include "Weapon.h"
#include "AK47.h"

Level::Level()
{
}


Level::~Level()
{
}

bool Level::saveLevel(const std::string name, const Player& player, const std::vector<Human*>& humans, const std::vector<Box>& boxes)
{
	std::ofstream level;
	level.open("Levels/" + name);
	if (level.fail()) {
		printf("Failed to create level: %s", name.c_str());
		return false;
	}

	//Humans
	level << humans.size()-1 << "\n";
	for (auto& human : humans) {
		if(human->isPlayer() == false)
			level << human->getPosition().x << ' ' << human->getPosition().y << ' ' << human->getDimension().x << ' ' << human->getDimension().y << ' ' << human->getTexture().filePath << ' '
			<< human->getPrimaryWeapon()->getName() << ' ' << human->getPrimaryWeapon()->getPosition().x << ' ' << human->getPrimaryWeapon()->getPosition().y << ' '
			<< human->getPrimaryWeapon()->getDimension().x <<  ' ' << human->getPrimaryWeapon()->getDimension().y << ' ' << human->getPrimaryWeapon()->getOrigin().x << ' ' << human->getPrimaryWeapon()->getOrigin().y << ' '
			<< human->getSecondaryWeapon()->getName() << ' ' << human->getSecondaryWeapon()->getPosition().x << ' ' << human->getSecondaryWeapon()->getPosition().y << ' '
			<< human->getSecondaryWeapon()->getDimension().x << ' ' << human->getSecondaryWeapon()->getDimension().y << ' ' << human->getSecondaryWeapon()->getOrigin().x << ' ' << human->getSecondaryWeapon()->getOrigin().y << "\n";
	}

	//Player
	level << player.getPosition().x << ' ' << player.getPosition().y << ' ' << player.getDimension().x << ' ' << player.getDimension().y << ' ' << player.getTexture().filePath << ' '
	<< player.getPrimaryWeapon()->getName() << ' ' << player.getPrimaryWeapon()->getPosition().x << ' ' << player.getPrimaryWeapon()->getPosition().y << ' '
	<< player.getPrimaryWeapon()->getDimension().x << ' ' << player.getPrimaryWeapon()->getDimension().y << ' ' << player.getPrimaryWeapon()->getOrigin().x << ' ' << player.getPrimaryWeapon()->getOrigin().y << ' '
	<< player.getSecondaryWeapon()->getName() << ' ' << player.getSecondaryWeapon()->getPosition().x << ' ' << player.getSecondaryWeapon()->getPosition().y << ' '
	<< player.getSecondaryWeapon()->getDimension().x << ' ' << player.getSecondaryWeapon()->getDimension().y << ' ' << player.getSecondaryWeapon()->getOrigin().x << ' ' << player.getSecondaryWeapon()->getOrigin().y << "\n";

	//Boxes
	level << boxes.size() << "\n";
	for (auto& box : boxes) {
		level << box.getPosition().x << ' ' << box.getPosition().y << ' ' << box.getDimension().x << ' ' << box.getDimension().y << ' ' << box.getTexture().filePath << "\n";
	}

	level.close();

	printf("Level %s Created!\n", name.c_str());
	return true;
}

bool Level::loadLevel(const std::string name, b2World* world, Player& player, std::vector<Human*>& humans, std::vector<Box>& boxes)
{
	std::ifstream level;
	level.open("Levels/" + name);
	if (level.fail()) {
		printf("Failed to open level: %s", name.c_str());
		return false;
	}

	{
		//humans
		glm::vec2 pos, dim;
		std::string texPath;
		int numHumans;
		level >> numHumans;
		for (int i = 0; i < numHumans; i++) {
			level >> pos.x >> pos.y >> dim.x >> dim.y >> texPath;
			Human h;
			h.humanInit(world, pos, dim, glm::vec2(10, 1), texPath);
			humans.push_back(&h);
		}
	}

	{
		//player
		glm::vec2 pos, dim;
		std::string texPath;
		std::string weaponName;
		level >> pos.x >> pos.y >> dim.x >> dim.y >> texPath;
		player.humanInit(world, pos, dim, glm::vec2(10, 1), texPath);
		for (int i = 0; i < 2; i++) {
			level >> weaponName;
			if (weaponName == "ak47") {
				glm::vec2 pos, dim, ori;
				level >> pos.x >> pos.y >> dim.x >> dim.y >> ori.x >> ori.y;
				player.addWeapon(new AK47(pos, dim, ori));
			}
		}
		humans.push_back(&player);
	}

	{
		//boxes
		glm::vec2 pos, dim;
		std::string texPath;
		int numBoxes;
		level >> numBoxes;
		for (int i = 0; i < numBoxes; i++) {
			level >> pos.x >> pos.y >> dim.x >> dim.y >> texPath;
			Box b;
			Texture tex = ResourceManager::loadTexture(texPath);
			b.init(world, pos, dim, tex);
			boxes.push_back(b);
		}
	}
	level.close();
	printf("Level %s Loaded!\n", name.c_str());

	return true;
}
