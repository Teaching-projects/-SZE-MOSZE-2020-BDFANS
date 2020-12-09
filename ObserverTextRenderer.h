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

    /**
     * @brief The function used to render the specified game instanse in text form 
     * 
     * @param ingame the game instance being rendered.
     * 
     */
    void render(const Game& ingame) const override;

    /**
     * @brief Construct a new ObserverTextRenderer object
     * 
     * @param in The ostream instance being used by the renderer
     */
    explicit ObserverTextRenderer(std::ostream& in) :TextRenderer(in) {};

    ///Default constructor
    ObserverTextRenderer() :TextRenderer() {}
};