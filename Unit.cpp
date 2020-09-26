#include "Unit.h"
#include <fstream>
#include <string>


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

Unit* Unit::praseUnit(std::string fnev) {
	std::ifstream fin(fnev);
	if (fin) {
		int health, dmg;
		std::string x, name;
		while (!fin.eof()) {
			std::getline(fin, x);
			std::string s;
			for (int i = 0; i < x.size(); i++) {

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
