/**
 * @file CharacterSVGRenderer.h
 * @class CharacterSVGRenderer
 * 
 * @brief The class resposible for rendering the heroe's vision in text form
 * 
 * @version 0.9.0
 * 
 * @date 2020-12-07
 * 
 */
#pragma once

#include "SVGRenderer.h"
#include "Game.h"

class CharacterSVGRenderer: public SVGRenderer
{

public:

    /**
     * @brief The function used to render the specified game instance from the heroe's viewpoint in SVG form 
     * 
     * @param ingame the game instance being rendered.
     * 
     */
    void render(const Game& ingame) const override;

    /**
     * @brief Construct a new CharacterSVGRenderer object
     * 
     * @param ofilename the name of the output file
     */
    explicit CharacterSVGRenderer(const std::string& ofilename) :SVGRenderer(ofilename) {};
};