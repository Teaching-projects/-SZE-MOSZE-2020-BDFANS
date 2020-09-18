#include "Battle.h"

void Battle(Unit& attacker, Unit& defender)
{
	std::cout << attacker;
	std::cout << defender;

		//exit with break?
		//while (attacker.getHealth() > 0 && defender.getHealth() > 0)
		while (true)
		{
			std::cout << attacker.getName() << " -> " << defender.getName() << std::endl;

			attacker.attack(defender);

			std::cout << attacker;
			std::cout << defender;

			if (defender.getHealth() > 0)
			{
				std::cout << defender.getName() << " -> " << attacker.getName() << std::endl;
				defender.attack(attacker);

				std::cout << attacker;
				std::cout << defender;


				if (attacker.getHealth() <= 0)
				{
					std::cout << attacker.getName() << " died. " << defender.getName() << " wins.\n";
					break;
				}
			}
			else
			{
				std::cout << defender.getName() << " died. " << attacker.getName() << " wins.\n";
				break;
			}
		}
	}