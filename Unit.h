/**
 * @file Unit.h
 * @class Unit
 *
 * @author BDFANS
 *
 * @brief header for Unit class
 * @version 0.3.0
 *
 *
 * @date 2020-10-15
 *
 */

#pragma once
#include <iostream>

class Unit
{
	std::string name;
	int maxhealth;
	int akthealth = maxhealth;
	int exp = 0;
	int lvl = 1;
	void gainExp(int xp);
	int damage; ///< the damage the character deals with a single attack
	double attackspeed; ///< the number of times the character can attack in a second
	double attackcooldown; ///< the remaining time, until the character can attack again

	/**
	 * @brief Set the Attack Cooldown object
	 *
	 * @param in new value for the units attackcooldown
	 *
	 * This function also prevents negative values by treating any possible negative inputs as 0
	 */
	void setAttackCooldown(double in);

	/**
	 * @brief this function executes the attack
	 *
	 * @param target the unit, who is being attacked
	 *
	 * This function also prevents negative values by treating any possible negative result as 0
	 */
	void attack(Unit& target);

public:

	///this is a getter function for name
	std::string getName() const { return name; }

	int getMaxHealth() const { return maxhealth; }
	int getAktHealth() const { return akthealth; }
	int getExp() const { return exp; }
	int getLvl() const { return lvl; }
	void setAktHealth(int i) { akthealth = i; }

	///this is a getter function for damage
	int getDamage() const { return damage; }
	///this is a getter function for attaclspeed
	double getAttackspeed() const { return attackspeed; }

	/**
	 * @brief Construct a new Unit object
	 *
	 * @param inn sets the name of the character. The default name is "default"
	 * @param inh sets the health of the character. The default health is 1
	 * @param ind sets the damage of the character. The default damage is 1
	 * @param ins sets the attackspeed of the character. The default speed is 1
	 *
	 * The constructor uses the attackspeed value to set the initial attackcooldown
	 */
	Unit(std::string inn = "default", int inh = 1, int ind = 1, double ins = 1) :name(inn), maxhealth(inh), damage(ind), attackspeed(ins)
	{
		attackcooldown = 1 / attackspeed;
	}

	/**
	 * @brief the functio responsible for deciding who attacks when based on the attackcooldown
	 *
	 * @param attacker the attacker unit
	 * @param defender the defender unit
	 *
	 * if the two units attackcooldown is equal, the attacker always goes first
	 */
	static void attackcd(Unit& attacker, Unit& defender);

	///overload of the << operator
	friend std::ostream& operator<<(std::ostream& os, const Unit& out);

	/**
	 * @brief JSON parser for Unit class
	 *
	 * @param fnev the name of the JSON file
	 * @return Unit* the pointer for the newly generated Unit object
	 *
	 * @throw Exception this function throws an exception if the file cannot be accessed
	 */
	static Unit* praseUnit(std::string fnev);

};