#pragma once
#include <iostream>

class Unit
{
	const std::string name;
	int health;
	int damage;

	void setHealth(int in);
	void setDamage(int in);

public:

	const std::string& getName() const { return name; }
	const int& getHealth() const { return health; }
	const int& getDamage() const { return damage; }


	Unit(std::string inn = "default", int inh = 1, int ind = 1) :name(inn), health(inh), damage(ind) {}

	static void Battle(Unit& attacker, Unit& defender);
	void attack(Unit& target);

	friend std::ostream& operator<<(std::ostream& os, const Unit& out);




};


