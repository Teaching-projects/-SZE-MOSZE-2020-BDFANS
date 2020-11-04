#pragma once

#include "Unit.h"

class Monster :public Unit
{


    public:

    static Monster parse(std::string filename);

    Monster(std::string innev,int inhp,int indmg,double inaspeed) :Unit(innev,inhp,indmg,inaspeed)  {}
};