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

std::ostream& operator<<(std::ostream& os, const Unit& out)
{
	os << out.getName() << ": HP: " << out.getHealth() << " DMG: " << out.getDamage() << std::endl;

	return os;
}

Unit* Unit::praseUnit(std::string fnev) {
	
	try
	{
		std::map<std::string,std::string> data = jsonparser::jsonparse_f(fnev);

		std::string innev = data.find("name")->second;
		int inhp = stoi(data.find("hp")->second);
		int indmg = stoi(data.find("dmg")->second);
		/* attackcooldown
		double inattackcd = stod(data,find("attackcooldown")-second);
		return new Unit(innev,inhp,indmg,inattackcd);
		*/
		return new Unit(innev,inhp,indmg);
	}
	catch(const std::exception& e)
	{
		throw  std::exception();
	}
};
