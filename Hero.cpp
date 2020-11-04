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
		if(data.count("name") > 0)
		{
		innev = data.get<std::string>("name");
		}
		if(data.count("base_health_points") > 0)
		{
		inhp = data.get<int>("base_health_points");
		}
		if(data.count("base_damage") > 0)
		{
		indmg = data.get<int>("base_damage");
		}
		if(data.count("base_attack_cooldown") > 0)
		{
		inaspeed = data.get<double>("base_attack_cooldown");
		}
        if(data.count("experience_per_level") > 0)
		{
		inexpreq = data.get<int>("experience_per_level");
		}
        if(data.count("health_point_bonus_per_level") > 0)
		{
		inhpb = data.get<int>("health_point_bonus_per_level");
		}
        if(data.count("damage_bonus_per_level") > 0)
		{
		indmgb = data.get<int>("damage_bonus_per_level");
		}
        if(data.count("cooldown_multiplier_per_level") > 0)
		{
		incdmul = data.get<double>("cooldown_multiplier_per_level");
		}
		return Hero(innev,inhp,indmg,inaspeed,inexpreq,inhpb,indmgb,incdmul);

	}
	catch(const JSON::ParseException& e)
	{
		throw  JSON::ParseException();
	}
 }