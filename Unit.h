#pragma once
#include <iostream>

class Unit
{
	const std::string name;
	int health;
	const int damage;


public:

	std::string getName() const { return name; }
	int getHealth() const { return health; }
	int getDamage() const { return damage; }


	Unit(std::string inn = "default", int inh = 1, int ind = 1) :name(inn), health(inh), damage(ind) {}

	//static void Battle(Unit& attacker, Unit& defender);
	void attack(Unit& target) const;

	friend std::ostream& operator<<(std::ostream& os, const Unit& out);




};


