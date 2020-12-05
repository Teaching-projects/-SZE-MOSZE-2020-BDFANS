/**
 * @file MarkedMap.h
 * @class MarkedMap
 *
 * @author BDFANS
 *
 * @brief header for MarkedMap class
 * @version 0.8.0
 *
 *
 * @date 2020-12-05
 *
 */
#pragma once

#include "Map.h"
#include <map>
#include <list>

class MarkedMap: public Map
{
    std::pair<int,int> hero_pos; //< location of the hero
    std::map<char,std::list<std::pair<int,int>>> monster_pos; //< list of monster IDs and locations

public:

    ///This exception is thrown when a positionfinder function can't find its target
    class NoInstanceException : public std::runtime_error {
       public:
        NoInstanceException(const std::string& errMsg) : std::runtime_error(errMsg) {};
    };

    ///This exception is thrown when the inputmap contains more than one heroes
    class MultipleHeroException : public std::runtime_error {
       public:
        MultipleHeroException(const std::string& errMsg) : std::runtime_error(errMsg) {};
    };

    /**
     * @brief Get the heros position (hero_pos)
     * 
     * @return std::pair<int,int> 
     * 
     * @throw NoInstanceException
     */
    std::pair<int,int> getHeroPosition() const;

    /**
     * @brief Get the list of all specified monstersIDs locations
     * 
     * @param c the searched monsterID
     * @return std::list<std::pair<int,int>> 
     * 
     * @throw NoInstanceException
     */
    std::list<std::pair<int,int>> getMonsterPositions(char c) const;

    /**
     * @brief loads and generates the map, and location data from file
     * 
     * @param filename name of the file used to generate the map and location data.
     * 
     * @throw MultipleHeroException
     */
    void loadMap(std::string filename);

    /**
     * @brief Construct an empty MarkedMap
     */
    MarkedMap() :hero_pos(std::make_pair(-1,-1)) {};

    /**
     * @brief Construc a MarkedMap object using a file
     * 
     * @param filename name of the file used to generate the map and location data.
     */
    MarkedMap(std::string filename) :hero_pos(std::make_pair(-1,-1)) {loadMap(filename);};
};