#include "SVGRenderer.h"


std::string SVGRenderer::getImage(std::string filename, int x, int y) const
{
    std::string out;

    std::ifstream f(filename);
    if(f.is_open())
    {
        f.close();
        out = "<image href=" + filename + "width=\"10\" height=\"10\"";
        out += "x=\"" + x*10;
        out +=  "\" y=\"" + y*10;
        out += "\" />\n";
    }
    else
    {
        f.close();
        out = "<rect fill=black width=\"10\" height=\"10\" ";
        out += "x=\"" + x*10;
        out +=  "\" y=\"" + y*10;
        out += "\" />\n";
    }
    
    return out;
}