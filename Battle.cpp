#include "Battle.h"

void Battle(Unit& attacker, Unit& defender)
{
	Unit Tattacker = attacker;
	Unit Tdefender = defender;
	while (true)
	{
		Tattacker.gainExp(Tattacker.attack(Tdefender));

		if (Tdefender.getaktHealth() > 0)
		{
			Tdefender.gainExp(Tdefender.attack(Tattacker));

			if (Tattacker.getaktHealth() <= 0)
			{
				defender.setUnit(Tdefender);
				attacker.setAkthp(0);
				std::cout << defender.getName() << " wins. Remaining HP: " <<defender.getmaxHealth()<<"/" <<defender.getaktHealth() << ".\n";
				break;
			}
		}
		else
		{
			attacker.setUnit(Tattacker);
			defender.setAkthp(0);
			std::cout << attacker.getName() << " wins. Remaining HP: " << attacker.getmaxHealth() << "/" << attacker.getaktHealth() << ".\n";
			break;
		}
		
	}
}
