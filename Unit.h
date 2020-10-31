#pragma once
#include <iostream>

class Unit
{
	std::string name;
	int maxhealth;
	int akthealth = maxhealth;
	int damage;
	int exp = 0;
	int lvl = 1;
	void gainExp(Unit* player, int xp);
public:

	std::string getName() const { return name; }
	int getMaxHealth() const { return maxhealth; }
	int getAktHealth() const { return akthealth; }
	int getDamage() const { return damage; }
	int getExp() const { return exp; }
	int getLvl() const { return lvl; }

	void setAktHealth(int i) { akthealth = i; }

	Unit(const std::string& inn = "default", int inh = 1, int ind = 1) :name(inn), maxhealth(inh), damage(ind) {}

	void attack(Unit& target);

	friend std::ostream& operator<<(std::ostream& os, const Unit& out);

	static Unit* praseUnit(std::string fnev);

};


