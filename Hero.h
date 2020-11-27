/**
 * @file Hero.h
 * @class Hero
 *
 * @author BDFANS
 *
 * @brief header for Hero class
 * @version 0.4.0
 *
 *
 * @date 2020-11-13
 *
 */
#pragma once

#include "Unit.h"

class Hero :public Unit
{
    
	int exp = 0; ///< Hero's current exp
	int lvl = 1; ///< Hero's current lvl
    const int exp_per_level; ///< Exp required for the next lvl
    const int hp_per_level; ///< HP bonus after a lvling up
    const int physicaldmg_per_level;///< Damage bonus after lvling up
    const int magicaldmg_per_level;///< Magical damage bonus per lvl
    const int defense_per_level;///< Defense bonus after lvling up
    const double cdmul_per_level; ///< Cooldown multiplier bonus after lvling up
    
    
    public:
    ///this is a getter function for current exp
	int getExp() const { return exp; }
    ///this is a getter function for current lvl
	int getLevel() const { return lvl; }

    /**
    * @brief JSON parser for Hero class
    *
    * @param filename is the name of the JSON file
    * @param innev sets the name of the hero. The default name is "default"
    * @param inhp sets the health of the hero. The default health is 1
    * @param indmg sets the damage of the hero. The default damage is 1
    * @param insaspeed sets the attackspeed of the hero. The default speed is 1.0
    * @param inhpb sets the health per level of the hero. The default health per level is 1
    * @param indmgb sets the damage per lvl of the hero. The default damage per level is 1
    * @param inexpreq sets the experience required for the next level for the hero. The default health required is 1
    * @param incdmul sets the cooldown multiplier bonus per lvl of the hero. The default cooldown multiplier is 1.0
    *
    * @return Hero object
    *
    * @throw Exception this function throws an exception if the file cannot be accessed
    */
    static Hero parse(std::string filename);

    /**
    * @param xp is the experience that the hero gains with each attack

    * the hero can only collect exp if he is below the max lvl
    * whenever the hero collets enough experience to level up, its stats will increase
    */
	void gainExp(int xp);

    /**
     * @brief this function executes a single attack
     *
     * @param target the unit, who is being attacked
     *
     * This function also prevents negative values by treating any possible negative result as 0
     */
    void attack(Unit& target);

    /**
     * @brief this function executes the fight
     *
     * @param defender the unit, who is being attacked
     *
     * This function will run untill an unit has atleast one health
     */
    void fightTilDeath(Unit& defender);
        
    /**
     * @brief Construct a new Unit object
     *
     * @param indmg sets the damage of the character.
     * @param innev sets the name of the character.
     * @param inhp sets the health of the character.
     * @param indef sets the defense of the character.
     * @param inaspeed sets the attackspeed of the character.
     * @param inexpreq sets the required experience of the character.
     * @param inhbp sets the bonus health per level of the character.
     * @param inphysb sets the bonus damage per level of the character.
     * @param inmagicb sets the bonus magical damage per level of the character.
     * @param indefb sets the bonus defense per level of the character.
     * @param incdmul sets the cooldown per level of the character.
     *
     * The constructor uses the attackspeed value to set the initial attackcooldown
     */
    Hero(std::string innev, int inhp,Damage indmg ,int indef, double inaspeed, int inexpreq = 1, int inhpb = 1, int inphysb = 1,int inmagicb = 1 ,int indefb = 1 ,double incdmul = 1)
        :Unit(innev,inhp,indmg,indef,inaspeed), exp_per_level(inexpreq), hp_per_level(inhpb), physicaldmg_per_level(inphysb),magicaldmg_per_level(inmagicb) ,defense_per_level(indefb) ,cdmul_per_level(incdmul) {}
};