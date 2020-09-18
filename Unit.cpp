#include "Unit.h"


void Unit::setHealth(int in)
{
	Unit::health = in;
}

void Unit::setDamage(int in)
{
	Unit::damage = in;
}


void Unit::attack(Unit& target)
{
	std::cout << name << " -> " << target.getName() << std::endl;

	if (target.getHealth() > damage)
	{
		target.setHealth(target.getHealth() - damage);
		
		std::cout << target;
	}
	else
	{
		target.setHealth(0);

		std::cout << target.getName() << " died. " << name << " wins.";
	}
}

//Static function
void Unit::Battle(Unit& attacker, Unit& defender)
{
	std::cout << attacker;
	std::cout << defender;

	while (attacker.getHealth() > 0 && defender.getHealth() > 0)
	{
		attacker.attack(defender);
		if (defender.getHealth() > 0)
		{
			defender.attack(attacker);
		}
	}
}


std::ostream& operator<<(std::ostream& os, const Unit& out)
{
	os << out.getName() << ": HP: " << out.getHealth() << " DMG: " << out.getDamage() << std::endl;

	return os;
}