/**
 * @file ObserverTextRenderer.h
 * @class ObserverTextRenderer
 * 
 * @author BDFANS
 * 
 * @brief The renderer for the entire map in text form
 * 
 * @version 0.9
 * 
 * @date 2020-12-06
 * 
 */
#pragma once

#include "TextRenderer.h"
#include "Game.h"

class ObserverTextRenderer: public TextRenderer
{

public:

    void render(const Game& ingame) const override;

    ObserverTextRenderer(std::ostream& in) :TextRenderer(in) {};

    ObserverTextRenderer() :TextRenderer() {}
};