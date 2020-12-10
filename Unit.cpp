#include "Unit.h"

 void Unit::attack(Unit& target)
{
	 int reduceddmg = damage.physical - target.getDefense();
	 int effectivedmg = damage.magical;
	 if ( reduceddmg > 0) {
		 effectivedmg += reduceddmg;
	 }
	 if (effectivedmg > 0) {
		 if (target.akthealth > effectivedmg)
		 {
			 target.akthealth -= effectivedmg;
		 }
		 else
		 {
			 target.akthealth = 0;
		 }
	 }
}

void Unit::setHealthPoints(int in)
{
	akthealth = in;
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
		attacker.attackcooldown = attacker.attackspeed;
		attacker.attack(defender);
	}
	else
	{
		attacker.setAttackCooldown(attacker.attackcooldown - defender.attackcooldown);
		defender.attackcooldown = defender.attackspeed;
		defender.attack(attacker);
	}
}

std::ostream& operator<<(std::ostream& os, const Unit& out)
{
	os << out.getName() << ": HP: " << out.getMaxHealthPoints() << " DMG: " << out.getDamage() << std::endl;

	return os;
}

bool Unit::isAlive()
	{
		if(akthealth > 0)
		{
			return true;
		}
		else
		{
			return false;
		}
		
	}

Unit::~Unit() {}