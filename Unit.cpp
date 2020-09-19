#include "Unit.h"


void Unit::attack(Unit& target) const
{
	if (target.health > damage)
	{
		target.health -= damage;
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