/**
 * @file SVGRenderer.h
 * @class SVGRenderer
 * 
 * @author BDFANS
 * 
 * @brief The abstract class used as the interface for text based maprendering solutions 
 * 
 * @version 0.9.0
 * 
 * @date 2020-12-07
 * 
 */
#pragma once

#include "Renderer.h"
#include <string>
#include <fstream>

class SVGRenderer: public virtual Renderer
{
protected:
    ///< the name of the file used as the output
    std::string outfilename;

    /**
     * @brief creates an SVG injection at the specified position 
     * 
     * @param filename name of the SVG file displayed
     * @param x the x position of the image (1 = 10 pixel)
     * @param y the y position of the image (1 = 10 pixel)
     * @return std::string returns a SVG formated imagerefence 
     */
    std::string getImage(std::string filename, int x, int y) const;

public:

    /**
     * @brief Construct a new SVGRenderer object
     * 
     * @param ofilename the name of the output file
     */
    explicit SVGRenderer(const std::string& ofilename) :outfilename(ofilename) {}

};