/**
 * @file Game.h
 * @class Game
 *
 * @author BDFANS
 *
 * @brief header for Game class
 * @version 0.7.0
 *
 *
 * @date 2020-11-30
 *
 */
#pragma once

#include "Map.h"
#include "Unit.h"
#include "Hero.h"
#include "Monster.h"
#include <iostream>
#include <string>
#include <list>

class Game
{
private:
    bool isHeroSet; //< Gives true if the hero is already set on the map.
    bool isMonsterSet; //< Gives true if the monster is already set on the map.
    bool isMapSet; //< Gives true if the map is already set.
    bool isStarted; //< Gives true if the game has already started.
    Hero* hero; //< The hero who plays.
    Map newMap; //< The map we are playing on.
    std::pair <int, int> h_location; //< The hero's location. (int, int)
    std::list<std::pair<Monster, std::pair<int, int>>> m_locations; //< Monsters list with locations.

    /**
     * @param int x Is the first coord.
     * @param int y Is the second coord.
     *
     * This function counts the monsters in one position
     */
    int getMonsterCountOnOnePos(int x, int y) const;

    /**
     * @param command - where we want to go
     *
     * This function is responsible for the movement of the character.
     * Also returns a true or false if the step was valid or not.
     */
    bool stepOn(std::string command);

public:


    /** this is a setter function for the map.
     *
     *@throw Exception this function throws an exception if we still have units on the map.
     *@throw Exception this function throws an exception if the game is still running
     */
    void setMap(Map map);

    /**
     *@param hero is the hero we want to put on the map.
     *@param x is the x coord.
     *@param y is the y coord.
     *
     *This function puts the hero to the given coords.
     *
     *@throw Exception this function throws an exception if we have already a hero on the map.
     *@throw Exception this function throws an exception if the coords are not valid.
     *@throw Exception this function throws an exception if the game is running.
     *@throw Exception this function throws an exception if we dont have a map to put on
     */
    void putHero(Hero hero, int x, int y);


    /**
     *@param monster is the monster we want to put on the map.
     *@param x is the x coord
     *@param y is the y coord
     *
     *This function puts a monster on the map.
     *
     *@throw Exception this function throws an exception if the coords are not valid.
     *@throw Exception this function throws an exception if we dont have a map to put on.
    */
    void putMonster(Monster monster, int x, int y);

    /**
     *This function is responsible for the gameplay
     *
     *@throw Exception this function throws an exception if the map or hero or monster is not set.
     */
    void run();

    /// This function shows the map with our current location
    void showMap();

    ///this is a constructor for empty game.
    Game();

    ///This is a constructor for game with the map initialized.
    Game(std::string mapfilename) : isHeroSet(false), isMonsterSet(false), isMapSet(false), isStarted(false), hero(nullptr) {};

    ///This is a destructor for game
    ~Game() { delete hero; }

    class OccupiedException : public std::runtime_error {
        public:
            OccupiedException(const std::string& errMsg) : std::runtime_error(errMsg) {}
    };

    class AlreadyHasHeroException : public std::runtime_error {
        public:
            AlreadyHasHeroException(const std::string& errMsg) : std::runtime_error(errMsg) {}
    };

    class AlreadyHasUnitException :public std::runtime_error {
        public:
            AlreadyHasUnitException(const std::string& errMsg) : std::runtime_error(errMsg){}
    };

    class GameAlreadyStartedException : public std::runtime_error {
        public:
            GameAlreadyStartedException(const std::string& errMsg) : std::runtime_error(errMsg) {}
    };

    class NotInitializedException : public std::runtime_error {
        public:
            NotInitializedException(const std::string& errMsg) : std::runtime_error(errMsg) {}
    };
};