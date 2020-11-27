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
			damage.physical += physicaldmg_per_level;
			damage.magical += magicaldmg_per_level;
			defense += defense_per_level;
			attackspeed *= cdmul_per_level;
			akthealth = maxhealth;

			attackcooldown = attackspeed;
		}
	}
}

 void Hero::attack(Unit& target)
{
	int effectivedmg = damage.magical + (damage.physical-target.getDefense());
	if (target.getHealthPoints() > effectivedmg)
	{
		target.setHealthPoints(target.getHealthPoints()-effectivedmg);
		gainExp(effectivedmg);
	}
	else
	{
		effectivedmg = target.getHealthPoints();
		gainExp(effectivedmg);
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
		int inmagic = 0;
		int inphys = 0;
		int inhp = 1;
		double inaspeed = 1.0;
        int inhpb = 1;
		int inphysb = 1;
		int inmagicb = 1;
		int indef = 1;
		int indefb = 1;
        int inexpreq = 1;
        double incdmul = 1;
		try
		{
		innev = data.get<std::string>("name");
		inhp = data.get<int>("base_health_points");
		inphys = data.get<int>("damage");
		inmagic = data.get<int>("magical-damage");
		indef = data.get<int>("defense");
		inaspeed = data.get<double>("base_attack_cooldown");
		inexpreq = data.get<int>("experience_per_level");
		inhpb = data.get<int>("health_point_bonus_per_level");
		inphysb = data.get<int>("physical_damage_bonus_per_level");
		inmagicb = data.get <int>("magical_damage_bonus_per_level");
		indefb = data.get<int>("defense_bonus_per_level");
		incdmul = data.get<double>("cooldown_multiplier_per_level");
		}
		catch(const std::exception& e)
		{
			std::cerr << "[ERROR] Missing value from input data! Make sure the JSON input data is valid!\n";
			continue;
		}
		
		
		return Hero(innev,inhp,inphys,inmagic,indef,inaspeed,inexpreq,inhpb,inphysb,inmagicb,indefb,incdmul);

	}
	catch(const JSON::ParseException& e)
	{
		throw  JSON::ParseException();
	}
 }