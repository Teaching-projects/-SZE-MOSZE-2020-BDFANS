/**
 * @file Hero.h
 * @class Hero
 *
 * @author BDFANS
 *
 * @brief header for Hero class
 * @version 0.5.0
 *
 *
 * @date 2020-11-27
 *
 */
#pragma once

#include "Unit.h"
#include "JSON.h"

class Hero :public Unit
{
    
	int exp = 0; ///< Hero's current exp
	int lvl = 1; ///< Hero's current lvl
    int exp_per_level; ///< Exp required for the next lvl
    int hp_per_level; ///< HP bonus after a lvling up
    int physicaldmg_per_level;///< Physical damage bonus after lvling up
    int magicaldmg_per_level;///< Magical damage bonus per lvl
    int defense_per_level;///< Defense bonus after lvling up
    double cdmul_per_level; ///< Cooldown multiplier bonus after lvling up
    int light_radius; ///< How far our hero can see.
    int light_radius_per_level; ///< How far our hero can see after lvling up
    
    
    public:
    ///this is a getter function for current exp
	int getExp() const { return exp; }
    ///this is a getter function for current lvl
	int getLevel() const { return lvl; }

    ///this is a getter function for light radius
    int getLightRadius() const { return light_radius; }

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
    void attack(Unit& target) override;

    /**
     * @brief this function executes the fight
     *
     * @param defender the unit, who is being attacked
     *
     * This function will run untill an unit has atleast one health
     */
    void fightTilDeath(Unit& defender);

    ///Constructor for empty hero
    Hero() {};
        
    /**
     * @brief Construct a new Unit object
     *
     * @param innev sets the name of the character.
     * @param inhp sets the health of the character.
     * @param inphys sets the physical damage of the character.
     * @param inmagic sets the magical damage of the character.
     * @param indef sets the defense of the character.
     * @param inaspeed sets the attackspeed of the character.
     * @param intexture sets the name of the texture file (*.SVG). The default is empty string
     * @param inexpreq sets the required experience of the character.
     * @param inhbp sets the bonus health per level of the character.
     * @param inphysb sets the bonus damage per level of the character.
     * @param inmagicb sets the bonus magical damage per level of the character.
     * @param indefb sets the bonus defense per level of the character.
     * @param incdmul sets the cooldown per level of the character.
     * @param inlr sets the light radius of the character.
     * @param inlrb sets the light radius per level of the character.
     *
     * The constructor uses the attackspeed value to set the initial attackcooldown
     */
    Hero(const std::string& innev, int inhp,int inphys, int inmagic ,int indef, double inaspeed,const std::string& intexture, int inexpreq = 1, int inhpb = 1, int inphysb = 1,int inmagicb = 1 ,int indefb = 1 ,double incdmul = 1, int inlr = 1, int inlrb = 1)
        :Unit(innev,inhp,inphys,inmagic,indef,inaspeed,intexture), exp_per_level(inexpreq), hp_per_level(inhpb), physicaldmg_per_level(inphysb),magicaldmg_per_level(inmagicb) ,defense_per_level(indefb) ,cdmul_per_level(incdmul), light_radius(inlr), light_radius_per_level(inlrb) {}
};