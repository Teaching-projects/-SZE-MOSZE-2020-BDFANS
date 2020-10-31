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

void Unit::setAttackCooldown(double in)
{
	if (in >= 0)
	{
		attackcooldown = in;
	}
	else
	{
		attackcooldown = 0;
	}


}

void Unit::attackcd(Unit& attacker, Unit& defender)
{
	if (attacker.attackcooldown <= defender.attackcooldown)
	{
		defender.setAttackCooldown(defender.attackcooldown - attacker.attackcooldown);
		attacker.attackcooldown = 1 / attacker.attackspeed;
		attacker.attack(defender);
	}
	else
	{
		attacker.setAttackCooldown(attacker.attackcooldown - defender.attackcooldown);
		defender.attackcooldown = 1 / defender.attackspeed;
		defender.attack(attacker);
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
			if (attackspeed * 1.10 < 100) { attackspeed = attackspeed * 1.10; }
			else { attackspeed = 100; };
			akthealth = maxhealth;
		}
	}
}

Unit* Unit::praseUnit(std::string fnev) {
	std::ifstream fin(fnev);
	if (fin) {
		int health = 0, dmg = 0;
		std::string x, name;
		double atckspd{};
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
			else if (s.find("attackcooldown") != std::string::npos) {
				atckspd = stod(s.substr(14));
			}
		}
		fin.close();
		return new Unit(name, health, dmg, atckspd);
	}
	else {
		throw std::exception();
		return nullptr;
	}
};
