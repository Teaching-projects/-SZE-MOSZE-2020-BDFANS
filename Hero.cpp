#include <climits>

#include "Hero.h"
#include "JSON.h"

void Hero::gainExp(int xp) {
	int maxlvl = 100;
	if (exp < INT_MAX - xp && lvl < maxlvl) {
		exp = exp + xp;
		while (exp >= exp_per_level && lvl < maxlvl) {
			lvl++;
			exp = exp - exp_per_level;
			maxhealth += hp_per_level;
			damage += dmg_per_level;
			attackspeed *= cdmul_per_level;
			akthealth = maxhealth;

			attackcooldown = attackspeed;
		}
	}
}

 void Hero::attack(Unit& target)
{
	int i = 0;
	if (target.getHealthPoints() > damage)
	{
		target.setHealthPoints(target.getHealthPoints()-damage);
		i = damage;
		gainExp(i);
	}
	else
	{
		i = target.getHealthPoints();
		gainExp(i);
		target.setHealthPoints(0);
	}
}



void Hero::fightTilDeath(Unit& defender)
{
	while (getHealthPoints() > 0 && defender.getHealthPoints() > 0)
	{
		attackcd(*this, defender);
	}
}

 Hero Hero::parse(std::string filename)
 {
     try
	{
		JSON data = JSON::parseFromFile(filename);
		std::string innev = "default";
		int inhp = 1;
		int indmg = 1;
		double inaspeed = 1.0;
        int inhpb = 1;
        int indmgb = 1;
        int inexpreq = 1;
        double incdmul = 1;
		try
		{
		innev = data.get<std::string>("name");
		inhp = data.get<int>("base_health_points");
		indmg = data.get<int>("base_damage");
		inaspeed = data.get<double>("base_attack_cooldown");
		inexpreq = data.get<int>("experience_per_level");
		inhpb = data.get<int>("health_point_bonus_per_level");
		indmgb = data.get<int>("damage_bonus_per_level");
		incdmul = data.get<double>("cooldown_multiplier_per_level");
		}
		catch(const std::exception& e)
		{
			std::cerr << "[ERROR] Missing value from input data! Make sure the JSON input data is valid!\n";
		}
		
		
		return Hero(innev,inhp,indmg,inaspeed,inexpreq,inhpb,indmgb,incdmul);

	}
	catch(const JSON::ParseException& e)
	{
		throw  JSON::ParseException();
	}
 }