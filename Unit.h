#pragma once
#include <iostream>

class Unit
{
	const std::string name;
	int maxhealth;
	int akthealth=maxhealth;
	int damage;
	int exp=0;
	int lvl=1;


public:

	std::string getName() const { return name; }
	int getaktHealth() const { return akthealth; }
	int getmaxHealth() const { return maxhealth; }
	int getDamage() const { return damage; }

	int getExp() const { return exp; }
	void gainExp(int xp);
	void setAkthp(int i) { akthealth = i; }
	int getLvl() const { return lvl; }
	Unit(const std::string &inn = "default", int inh = 1, int ind = 1) :name(inn), maxhealth(inh), damage(ind) {}

	int attack(Unit& target) const;

	friend std::ostream& operator<<(std::ostream& os, const Unit& out);

	static Unit* praseUnit(std::string fnev);

};


