#include "Weapon.h"


Weapon::Weapon(Agent& parent, FireType & fireType, const Texture & weapon, const std::string & name) : _parent(parent), _fireMode(fireType), _weapon(weapon), _name(name)
{
}

Weapon::~Weapon()
{
}

void Weapon::update()
{
}

void Weapon::render()
{
}
