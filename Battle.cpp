#include "Battle.h"

void Battle(Unit& attacker, Unit& defender)
{

	while (attacker.getHealth() > 0 && defender.getHealth() > 0)
	{	
		Unit::attackcd(attacker,defender);
	}

	if(attacker.getHealth() > 0)
	{
		std::cout << attacker.getName() << " wins. Remaining HP: " << attacker.getHealth() << ".\n";
	}
	else
	{
		std::cout << defender.getName() << " wins. Remaining HP: " << defender.getHealth() << ".\n";

	}
	
}
