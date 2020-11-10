#pragma once

#include "Unit.h"

class Hero :public Unit
{
    
	int exp = 0; //jelenlegi XP
	int lvl = 1; //jelenlegi szint
    const int exp_per_level; //XP szügséges a szintlépéshez
    const int hp_per_level; //HP bónusz szintlépésenként
    const int dmg_per_level; //DMG bónusz szintlépésenként
    const double cdmul_per_level; //cooldown szorzó szintlépésenként
    
    
    public:

	int getExp() const { return exp; }
	int getLevel() const { return lvl; }


    static Hero parse(std::string filename);
	void gainExp(int xp);

    void attack(Unit& target);
    void fightTilDeath(Unit& defender);
        
    Hero(std::string innev, int inhp, int indmg, double inaspeed, int inexpreq, int inhpb, int indmgb, double incdmul) 
        :Unit(innev,inhp,indmg,inaspeed), exp_per_level(inexpreq), hp_per_level(inhpb), dmg_per_level(indmgb), cdmul_per_level(incdmul) {}
};