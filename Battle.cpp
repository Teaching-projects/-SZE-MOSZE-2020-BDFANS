#include "Battle.h"

void Battle(Unit& attacker, Unit& defender)
{

	while (attacker.getAktHealth() > 0 && defender.getAktHealth() > 0)
	{
		Unit::attackcd(attacker, defender);
	}

	if (attacker.getAktHealth() > 0)
	{
		std::cout << attacker.getName() << " wins. Remaining HP: " << attacker.getAktHealth() << ".\n";
	}
	else
	{
		std::cout << defender.getName() << " wins. Remaining HP: " << defender.getAktHealth() << ".\n";

	}

}