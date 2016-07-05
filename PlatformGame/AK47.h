#pragma once

#include "Weapon.h"

class AK47 : public Weapon
{
public:
	AK47(const glm::vec2& position, const glm::vec2& dimension, const glm::vec2& origin);
	AK47(const glm::vec2& position, const glm::vec2& origin);

	~AK47();

private:
	void initStats(const glm::vec2& position);
};

