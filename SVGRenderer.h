#pragma once

#include "Renderer.h"
#include <string>
#include <fstream>

class SVGRenderer: virtual Renderer
{
protected:
    ///< the name of the file used as the output
    std::string outfilename;

    std::string getImage(std::string filename, int x, int y) const;

public:

    SVGRenderer(std::string ofilename) :outfilename(ofilename) {}

};