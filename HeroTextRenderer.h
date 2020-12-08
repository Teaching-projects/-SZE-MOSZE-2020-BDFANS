/**
 * @file HeroTextRenderer.h
 * 
 * @brief The class resposible for rendering the heroe's vision in text form
 * 
 * @version 0.9.0
 * 
 * @date 2020-12-06
 * 
 */
#pragma once

#include "TextRenderer.h"
#include "Game.h"

class HeroTextRenderer: public TextRenderer
{

public:
    void render(const Game& ingame) const;

    HeroTextRenderer(std::ostream& in) :TextRenderer(in) {};

    HeroTextRenderer() :TextRenderer() {}
};