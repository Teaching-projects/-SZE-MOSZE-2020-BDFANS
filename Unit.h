#pragma once
#include <iostream>

class Unit
{
	std::string name;
	int health;
	int damage;

public:

	const std::string& getName() const { return name; }
	const int& getHealth() const { return health; }
	const int& getDamage() const { return damage; }

	void setHealth(const int& in);
	void setDamage(const int& in);


	Unit(std::string inn = "default", int inh = 1, int ind = 1) :name(inn), health(inh), damage(ind) {}

	static void Battle(Unit& attacker, Unit& defender);
	int attack(Unit& target);

	friend std::ostream& operator<<(std::ostream& os, const Unit& out);




};


