#include "Unit.h"
#include <fstream>
#include <string>
#include "jsonparser.h"


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

void Unit::setAttackCooldown(double in)
{
	if(in >= 0)
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
	if(attacker.attackcooldown <= defender.attackcooldown)
	{
		defender.setAttackCooldown(defender.attackcooldown - attacker.attackcooldown);
		attacker.attackcooldown = 1/attacker.attackspeed;
		attacker.attack(defender);
	}
	else
	{
		attacker.setAttackCooldown(attacker.attackcooldown - defender.attackcooldown);
		defender.attackcooldown = 1/defender.attackspeed;
		defender.attack(attacker);
	}
}

std::ostream& operator<<(std::ostream& os, const Unit& out)
{
	os << out.getName() << ": HP: " << out.getHealth() << " DMG: " << out.getDamage() << std::endl;

	return os;
}

Unit* Unit::praseUnit(std::string fnev) {
	try
	{
		std::map<std::string,std::string> data = jsonparser::jsonparse_f(fnev);
		std::string innev = "default";
		int inhp = 1;
		int indmg = 1;
		double inaspeed;
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
