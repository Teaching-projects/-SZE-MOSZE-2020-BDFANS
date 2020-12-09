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

#include "Renderer.h"

class Game
{
private:
    bool isHeroSet; ///< Gives true if the hero is already set on the map.
    bool isMonsterSet; ///< Gives true if the monster is already set on the map.
    bool isMapSet; ///< Gives true if the map is already set.
    bool isStarted; ///< Gives true if the game has already started.
    Hero* gamehero; ///< The hero who plays.
    Map newMap; ///< The map we are playing on.
    std::list<std::pair<Monster, std::pair<int, int>>> m_locations; ///< Monsters list with locations.
    std::pair<int, int > h_location; ///< Heroe's location

    std::list<Renderer*> rendererlist; ///< The list of renderers being used by the game

    std::string wall_texture; ///< texturefile of wall
    std::string free_texture; ///< texturefile of free space


    /**
     * @param command - where we want to go
     *
     * This function is responsible for the movement of the character.
     * Also returns a true or false if the step was valid or not.
     */
    bool stepOn(const std::string& command);

    /**
     * @brief This runs all registered renderers
     */
    void renderall();

public:

    /**
     *This function is responsible for the gameplay
     *
     *@throw NotInitializedException this function throws an exception if the map or hero or monster is not set.
     */
    void run();

    ///this is a constructor for empty game.
    Game() :isHeroSet(false), isMonsterSet(false), isMapSet(false), isStarted(false), gamehero(nullptr){};

    ///This is a constructor for game with the map initialized.
    Game(std::string& mapfilename) : isHeroSet(false), isMonsterSet(false), isMapSet(true), isStarted(false), gamehero(nullptr), newMap(Map(mapfilename)) {};

    ///This is a destructor for game
    ~Game();

    /** this is a setter function for the map.
     *
     *@throw AlreadyHasUnitException this function throws an exception if we still have units on the map.
     *@throw GameAlreadyStartedException this function throws an exception if the game is still running
     */
    void setMap(const Map& map);

    /**
     * @brief returns the stored map
     * 
     * @return Map 
     */
    Map getmap() const {return newMap;};

    /**
     * @param int x Is the first coord.
     * @param int y Is the second coord.
     *
     * This function counts the monsters in one position
     */
    int getMonsterCountOnOnePos(int x, int y) const;
    

    /**
     * @brief return the heroe's pointer
     * 
     * @return Hero* 
     */
    Hero* getHero() const {return gamehero;}

    /**
     * @brief return the heroe's location
     * 
     * @return std::pair<int, int> 
     */
    std::pair<int, int> getHeroPos() const {return h_location;}

    /**
     *@param hero is the hero we want to put on the map.
     *@param x is the x coord.
     *@param y is the y coord.
     *
     *This function puts the hero to the given coords.
     *
     *@throw AlreadyHasHeroException this function throws an exception if we have already a hero on the map.
     *@throw OccupiedException this function throws an exception if the coords are not valid.
     *@throw GameAlreadyStartedException this function throws an exception if the game is running.
     *@throw WrongIndexException this function throws an exception if we dont have a map to put on
     */
    void putHero(Hero hero, int x, int y);

    /**
     *@param monster is the monster we want to put on the map.
     *@param x is the x coord
     *@param y is the y coord
     *
     *This function puts a monster on the map.
     *
     *@throw OccupiedException this function throws an exception if the coords are not valid.
     *@throw WrongIndexException this function throws an exception if we dont have a map to put on.
    */
    void putMonster(Monster monster, int x, int y);


    /**

     *@param x is the unit's x coord
     *@param y is the unit's y coord
     *
     *This function checks if the unit is on the map
    */
    bool heroIsOnMap(int x, int y);

    /**
     * @brief this function registers new renderers
     * 
     * @param inrender 
     */
    void registerRenderer(Renderer* inrender);
    
    

    /**
     * @brief Get a list of monsters on a certain coordinate. Returns empty list, if there are no monsters on map
     * 
     * @param x the X coordinate
     * @param y the Y coordinate
     * @return std::list<Monster> generated list of monsters
     * 
     */
    std::list<Monster> getMonstersonPos(int x, int y) const;

    /**
     * @brief Set the access path to the walls texture
     * 
     * @param filename the name of the file containing the texture
     */
    void setWallTexture(const std::string& filename) {wall_texture = filename;};

    /**
     * @brief Set the access path to the free space texture
     * 
     * @param filename the name of the file containing the texture
     */
    void setFreeTexture(const std::string& filename) {free_texture = filename;};

    ///this is the getter function for the wall_texture
    std::string getWallTexture() const {return wall_texture;};

    ///this is the getter function for the free_texture
    std::string getFreeTexture() const {return free_texture;};

    ///This exception is thrown when the target location on the map is already occupied
    class OccupiedException : public std::runtime_error {
        public:
            explicit OccupiedException(const std::string& errMsg) : std::runtime_error(errMsg) {}
    };

    ///This exception is thrown when attemptint to place a hero on a map that already has a hero
    class AlreadyHasHeroException : public std::runtime_error {
        public:
            explicit AlreadyHasHeroException(const std::string& errMsg) : std::runtime_error(errMsg) {}
    };

    ///This exception is thrown when attemptint to place a hero on top a monster
    class AlreadyHasUnitException :public std::runtime_error {
        public:
            explicit AlreadyHasUnitException(const std::string& errMsg) : std::runtime_error(errMsg){}
    };

    ///This exception is thrown when attempting to run the same game instance twice
    class GameAlreadyStartedException : public std::runtime_error {
        public:
            explicit GameAlreadyStartedException(const std::string& errMsg) : std::runtime_error(errMsg) {}
    };

    ///This exception is thrown when attempting to run the game without proper initialization
    class NotInitializedException : public std::runtime_error {
        public:
            explicit NotInitializedException(const std::string& errMsg) : std::runtime_error(errMsg) {}
    };
};