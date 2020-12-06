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

#include "Game.h"
#include <string>

class PreparedGame : Game {
    public:
        PreparedGame(std::string jsongame);

        void runGame();
};