#pragma once

#include "Map.h"
#include <Map>
#include <List>

class MarkedMap: public Map
{
    std::pair<int,int> hero_pos;
    std::map<char,std::list<std::pair<int,int>>> monster_pos;

public:

    class NoInstanceException : public std::runtime_error {
       public:
        NoInstanceException(const std::string& errMsg) : std::runtime_error(errMsg) {};
    };

    class MultipleHeroException : public std::runtime_error {
       public:
        MultipleHeroException(const std::string& errMsg) : std::runtime_error(errMsg) {};
    };

    std::pair<int,int> getHeroPosition() const;

    std::list<std::pair<int,int>> getMonsterPositions(char c) const;

    void loadMap(std::string filename);

    MarkedMap() :hero_pos(std::make_pair(-1,-1)) {};

    MarkedMap(std::string filename) :hero_pos(std::make_pair(-1,-1)) {loadMap(filename);};
};