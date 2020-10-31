#include "Unit.h"
#include <fstream>
#include <string>
#include <cmath>
#include <climits>

void Unit::attack(Unit& target)
{
	int i = 0;
	if (target.akthealth > damage)
	{
		target.akthealth -= damage;
		i = damage;
		Unit::gainExp(i);
	}
	else
	{
		i = target.akthealth;
		Unit::gainExp(i);
		target.akthealth = 0;
	}
}

std::ostream& operator<<(std::ostream& os, const Unit& out)
{
	os << out.getName() << ": HP: " << out.getMaxHealth() << " DMG: " << out.getDamage() << std::endl;

	return os;
}

void Unit::gainExp(int xp) {
	int maxlvl = 100;
	if (exp < INT_MAX - xp and lvl < maxlvl) {
		exp = exp + xp;
		int lvlup = 100;
		while (exp >= lvlup and lvl < maxlvl) {
			lvl++;
			exp = exp - lvlup;
			if (maxhealth < INT_MAX - nearbyint(maxhealth * 0.10)) {
				maxhealth = nearbyint(maxhealth * 1.10);
			}
			if (damage < INT_MAX - nearbyint(maxhealth * 0.10)) { damage = nearbyint(damage * 1.10); };
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
