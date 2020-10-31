#include "Battle.h"

void Battle(Unit& attacker, Unit& defender)
{
	Unit Tattacker = attacker;
	Unit Tdefender = defender;
	while (true)
	{
		Tattacker.attack(Tdefender);

		if (Tdefender.getAktHealth() > 0)
		{
			Tdefender.attack(Tattacker);

			if (Tattacker.getAktHealth() <= 0)
			{
				defender = Tdefender;
				attacker.setAktHealth(0);
				std::cout << defender.getName() << " wins. Remaining HP: " << defender.getAktHealth() << ".\n";
				break;
			}
		}
		else
		{
			attacker = Tattacker;
			defender.setAktHealth(0);
			std::cout << attacker.getName() << " wins. Remaining HP: " << attacker.getAktHealth() << ".\n";
			break;
		}

	}
}
