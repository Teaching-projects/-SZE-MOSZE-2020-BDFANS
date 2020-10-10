#include "Unit.h"
#include <fstream>
#include <string>
#include <math.h>
#include <climits>

int Unit::attack(Unit& target) const
{
	if (target.akthealth > damage)
	{
		target.akthealth -= damage;
		return damage;
	}
	else
	{
		int i = target.akthealth;
		target.akthealth = 0;
		return i;
	}
}

std::ostream& operator<<(std::ostream& os, const Unit& out)
{
	os << out.getName() << ": HP: " << out.getmaxHealth() << " DMG: " << out.getDamage() << std::endl;

	return os;
}

void Unit::setUnit(Unit player) {
	damage = player.damage;
	akthealth = player.akthealth;
	maxhealth = player.maxhealth;
	exp = player.exp;
	lvl = player.lvl;
}

void Unit::gainExp(int xp) {
	int maxlvl=100;
	if (exp < INT_MAX - xp and lvl<maxlvl) {
		exp = exp + xp;
		int lvlup = 100;
		while (exp >= lvlup and lvl < maxlvl) {
			lvl++;
			std::cout << "lvl " << lvl;
			exp = exp - lvlup;
			if (maxhealth < INT_MAX - nearbyint(maxhealth*0.10)) {
				maxhealth = nearbyint(maxhealth * 1.10);
			}
			if (damage < INT_MAX -nearbyint(maxhealth*0.10)) { damage = nearbyint(damage * 1.10); };
			akthealth = maxhealth;
		}
	}
}

Unit* Unit::praseUnit(std::string fnev) {
	std::ifstream fin(fnev);
	if (fin) {
		int health=0, dmg=0;
		std::string x, name;
		while (!fin.eof()) {
			std::getline(fin, x);
			std::string s;
			for (int i = 0; i < static_cast<int>(x.size()); i++) {

				if ((x[i] >= 'A' && x[i] <= 'Z') ||
					(x[i] >= 'a' && x[i] <= 'z') ||
					(x[i] >= '0' && x[i] <= '9'))
				{
					s = s + x[i];
				}
			}
			if (s.find("name") != std::string::npos) {
				name = s.substr(4);
			}
			else if (s.find("hp") != std::string::npos) {
				health = stoi(s.substr(2));
			}
			else if (s.find("dmg") != std::string::npos) {
				dmg = stoi(s.substr(3));
			}
		}
		fin.close();
		return new Unit(name, health, dmg);
	}
	else {
		throw std::exception();
		return nullptr;
	}
};
