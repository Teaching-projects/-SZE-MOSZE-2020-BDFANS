/**
 * @file Unit.h
 * @class Unit
 *
 * @author BDFANS
 *
 * @brief header for Unit class
 * @version 0.5.0
 *
 *
 * @date 2020-11-27
 *
 */

#pragma once

#include "JSON.h"
#include "Damage.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <climits>

class Unit
{
protected:

	std::string name; ///< Character's name 
	int maxhealth; ///< Character's total health pool 
	int akthealth = maxhealth; ///< current health before character dies
	Damage damage; ///< Damage is a struct which contains int physical and int magical dmg. Physical damage can be reduced by defense.
	int defense; ///< Defense can only block physical damage;
	double attackspeed; ///< the number of times the character can attack in a second
	double attackcooldown; ///< the remaining time, until the character can attack again 

	std::string texture; ///< The Units texture

	/**
	 * @brief Set the Attack Cooldown object
	 *
	 * @param in new value for the units attackcooldown
	 *
	 * This function also prevents negative values by treating any possible negative inputs as 0
	 */
	void setAttackCooldown(double in);



	/**
	 * @brief this function executes a single attack
	 *
	 * @param target the unit, who is being attacked
	 *
	 * This function also prevents negative values by treating any possible negative result as 0
	 */
	virtual void attack(Unit& target);

public:

	///this is a getter function for name
	std::string getName() const { return name; }

	///this is a getter function for Max Health points
	int getMaxHealthPoints() const { return maxhealth; }

	///this is a getter function for the current health points 
	int getHealthPoints() const { return akthealth; }

	/**
	* @brief this is a setter for the current health points

	* @param i sets the current health;
	*/
	void setAktHealth(int i) { akthealth = i; }

	///this is a getter function for defense
	int getDefense() const { return defense; }
	///this getter function returns a damage struct
	Damage getDamage() const { return damage; }
	///this is a getter function for physical damage
	int getPhysicalDamage() const { return damage.physical; }
	///this is a getter function for magical damage
	int getMagicalDamage() const { return damage.magical; }
	///this is a getter function for attackspeed
	double getAttackCoolDown() const { return attackspeed; }

	/**
	 * @brief Construct a new Unit object
	 *
	 * @param inn sets the name of the character. The default name is "default"
	 * @param inh sets the health of the character. The default health is 1
	 * @param inphys sets the physical damage of the character. The default physical damage is 1
	 * @param inmagic sets te magical damage of te chharacter. The default magical damage is 1
	 * @param indef sets the defense of the caracter. The default defense is 1
	 * @param ins sets the attackspeed of the character. The default speed is 1
	 * @param intexture sets the name of the texture file (*.SVG). The default is empty string
	 * 
	 * The constructor uses the attackspeed value to set the initial attackcooldown
	 */
	Unit(const std::string& inn = "default", int inh = 1,int inphys = 1, int inmagic = 1, int indef=1, double ins = 1, const std::string& intexture = "") :name(inn), maxhealth(inh), damage(inphys,inmagic) ,defense(indef), attackspeed(ins), texture(intexture)
	{
		attackcooldown = attackspeed;
	}

	///Virtual destructor to avoid potential memoryleak with Hero class
	virtual ~Unit();

	/**
	 * @brief the function responsible for deciding who attacks when based on the attackcooldown
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
	 * @param fnev the name of the JSON file we read from
	 * @return Unit* the pointer for the newly generated Unit object
	 *
	 * @throw Exception this function throws an exception if the file cannot be accessed
	 */
	static Unit praseUnit(std::string fnev);

	/**
	 * @brief checks if character is still alive
	 * @return with true or false
	 */
	bool isAlive();

	/**
	* @brief this is a setter for current health points
	* @param in sets the current health
	*/
	void setHealthPoints(int in);

	///this is the getter function for the texture
	std::string getTexture() {return texture;}

};