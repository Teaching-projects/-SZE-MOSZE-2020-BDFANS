#include "Unit.h"
#include <fstream>
#include <string>
#include "jsonparser.h"
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
	if (exp < INT_MAX - xp && lvl < maxlvl) {
		exp = exp + xp;
		int lvlup = 100;
		while (exp >= lvlup && lvl < maxlvl) {
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
	try
	{
		std::map<std::string,std::string> data = jsonparser::jsonparse_f(fnev);
		std::string innev = "default";
		int inhp = 1;
		int indmg = 1;
		double inaspeed = 1.0;
		if(data.count("name") > 0)
		{
		innev = data.find("name")->second;
		}
		if(data.count("hp") > 0)
		{
		inhp = stoi(data.find("hp")->second);
		}
		if(data.count("dmg") > 0)
		{
		indmg = stoi(data.find("dmg")->second);
		}
		if(data.count("attackcooldown") > 0)
		{
		inaspeed = stod(data.find("attackcooldown")->second);
		}
		return new Unit(innev,inhp,indmg,inaspeed);

	}
	catch(const std::exception& e)
	{
		throw  std::exception();
	}
};
