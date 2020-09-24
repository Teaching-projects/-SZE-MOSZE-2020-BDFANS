#include "Battle.h"

void Battle(Unit& attacker, Unit& defender)
{
	while (true)
	{

		attacker.attack(defender);

		if (defender.getHealth() > 0)
		{
			defender.attack(attacker);

			if (attacker.getHealth() <= 0)
			{
				std::cout /*<< attacker.getName() << " died. "*/ << defender.getName() << " wins. Remaining HP: " << defender.getHealth() << ".\n";
				break;
			}
		}
		else
		{
			std::cout /*<< attacker.getName() << " died. "*/ << attacker.getName() << " wins. Remaining HP: " << attacker.getHealth() << ".\n";
			break;
		}
	}
}
