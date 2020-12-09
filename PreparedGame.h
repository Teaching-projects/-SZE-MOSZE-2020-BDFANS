/**
 * @file PreparedGame.h
 * @class PreparedGame
 *
 * @author BDFANS
 *
 * @brief header for PreparedGame class
 * @version 0.8.0
 *
 *
 * @date 2020-12-06
 *
 */
#pragma once

#include "Game.h"
#include <string>

class PreparedGame : Game {
    public:
        /**
         *This function prepares the game from a file.
         *@param string jsongame is the preparedgame file.
         */
        PreparedGame(std::string jsongame);

        ///This function runs the game.
        void runGame();

        /**
        * @brief this function registers new renderers
        * 
        * @param inrender the input renderer
        */
        void registerRenderer(Renderer* inrender);
};