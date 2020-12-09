/**
 * @file ObserverSVGRenderer.h
 * @class ObserverSVGRenderer
 * 
 * @author BDFANS
 * 
 * @brief The renderer for the entire map in SVG form
 * 
 * @version 0.9
 * 
 * @date 2020-12-07
 * 
 */
#pragma once

#include "SVGRenderer.h"
#include "Game.h"

class ObserverSVGRenderer : public SVGRenderer
{

public:

    /**
     * @brief The function used to render the specified game instanse in SVG form 
     * 
     * @param ingame the game instance being rendered.
     * 
     */
    void render(const Game& ingame) const override;

    /**
     * @brief Construct a new ObserverSVGRenderer object
     * 
     * @param ofilename the name of the output file
     */
    explicit ObserverSVGRenderer(const std::string& ofilename) :SVGRenderer(ofilename) {};

};