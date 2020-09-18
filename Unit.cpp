#include "Unit.h"

/*
void Unit::setHealth(int in)
{
	Unit::health = in;
}
*/

/*
void Unit::setDamage(int in)
{
	Unit::damage = in;
}
*/

void Unit::attack(Unit& target) const
{
	if (target.health > damage)
	{
		target.health = target.health - damage;
	}
	else
	{
		target.health = 0;
	}
}

std::ostream& operator<<(std::ostream& os, const Unit& out)
{
	os << out.getName() << ": HP: " << out.getHealth() << " DMG: " << out.getDamage() << std::endl;

	return os;
}