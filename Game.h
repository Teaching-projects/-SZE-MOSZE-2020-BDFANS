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
    const std::string TOP_LEFT = "\u2554";
    const std::string TOP_RIGHT = "\u2557";
    const std::string BOTTOM_LEFT = "\u255A";
    const std::string BOTTOM_RIGHT = "\u255D";
    const std::string HORIZONTAL = "\u2550\u2550";
    const std::string VERTICAL = "\u2551";
    const std::string FREE = "\u2591\u2591";
    const std::string WALL = "\u2588\u2588";
    const std::string SINGLEMONSTER = "M\u2591";
    const std::string MULTIPLEMONSTERS = "MM";
    const std::string HERO = "\u2523\u252B";

    bool isHeroSet; //< Gives true if the hero is already set on the map.
    bool isMonsterSet; //< Gives true if the monster is already set on the map.
    bool isMapSet; //< Gives true if the map is already set.
    bool isStarted; //< Gives true if the game has already started.
    Hero* gamehero; //< The hero who plays.
    Map newMap; //< The map we are playing on.
    std::list<std::pair<Monster, std::pair<int, int>>> m_locations; //< Monsters list with locations.
    std::pair<int, int > h_location;

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
     *@param x is the unit's x coord
     *@param y is the unit's y coord
     *
     *This function checks if the unit is on the map
    */
    bool heroIsOnMap(int x, int y);

    /// This function shows the map with our current location
    void showMap();

    ///This function shows the hero's current vision
    void showHeroVision();

public:

    /**
     *This function is responsible for the gameplay
     *
     *@throw Exception this function throws an exception if the map or hero or monster is not set.
     */
    void run();

    ///this is a constructor for empty game.
    Game();

    ///This is a constructor for game with the map initialized.
    Game(std::string& mapfilename) : isHeroSet(false), isMonsterSet(false), isMapSet(true), isStarted(false), gamehero(nullptr), newMap(Map(mapfilename)) {};

    ///This is a destructor for game
    ~Game() { delete gamehero; };

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