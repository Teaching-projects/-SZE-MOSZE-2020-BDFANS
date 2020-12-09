/**
 * @file HeroTextRenderer.h
 * @class HeroTextRenderer
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

    /**
     * @brief The function used to render the specified game instance from the heroe's viewpoint in text form 
     * 
     * @param ingame the game instance being rendered.
     * 
     */
    void render(const Game& ingame) const override;

    /**
     * @brief Construct a new HeroTextRenderer object
     * 
     * @param in The ostream instance being used by the renderer
     */
    explicit HeroTextRenderer(std::ostream& in) :TextRenderer(in) {};

    ///Default constructor
    HeroTextRenderer() :TextRenderer() {}
};