#include "SVGRenderer.h"


std::string SVGRenderer::getImage(std::string filename, int x, int y) const
{
    std::string out;

    std::ifstream f(filename);
    if(f.is_open())
    {
        f.close();
        out = "<image href=\"" + filename + "\" width=\"10\" height=\"10\" ";
        if(x != 0)
        out += "x=\"" + std::to_string(x*10);
        else {out += "x=\"0";}
        
        if(y != 0)
        out +=  "\" y=\"" + std::to_string(y*10);
        else { out += "\" y=\"0";}
        out += "\" />\n";
    }
    else
    {
        f.close();
        out = "<rect fill=\"black\" width=\"10\" height=\"10\" ";
        if(x != 0)
        out += "x=\"" + std::to_string(x*10);
        else {out += "x=\"0";}

        if(y != 0)
        out +=  "\" y=\"" + std::to_string(y*10);
        else { out += "\" y=\"0";}
        out += "\" />\n";
    }
    return out;
}