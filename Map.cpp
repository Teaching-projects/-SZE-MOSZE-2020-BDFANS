#include "Map.h"

#include <fstream>
#include <string>
#include <algorithm>


/**
 * @brief Construct a new Map:: Map object
 * 
 * @param filename the name of the file used to generate the map
 */
Map::Map(std::string filename) {
    loadMap(filename);
}

void Map::loadMap(std::string filename){
    std::ifstream infile(filename);
    if (infile)
    {
        std::string instring;
        //generate initial map
        int inX = 0;
        int inY = 0;
        while (std::getline(infile, instring))
        {
            if(instring.size() > 0)
            {
            inY++;
            inX = std::max(inX, (int)instring.length());
            }
            else {}
        }
        lenX = inX;
        lenY = inY;
        loadedmap = MAPMATRIX(lenY, std::vector<type>(lenX, type::Wall));

        //load map features
        infile.clear();
        infile.seekg(0);
        inY = 0;
        while (std::getline(infile, instring))
        {
            if(instring.size() > 0) {
            for (inX = 0; inX < (int)instring.length(); inX++)
            {
                switch (instring[inX])
                {
                case '#':
                    loadedmap[inY][inX] = type::Wall;
                    break;

                case ' ':
                    loadedmap[inY][inX] = type::Free;
                    break;

                default:
                    break;
                }
            }
            inY++;
            }
        }
        infile.close();
    }
    else
    {
        throw Map::WrongIndexException("Couldn't load the map!");
    }

}


type Map::get(int x, int y) const
{
    if(x < lenX && y < lenY)
    {
         return loadedmap[y][x];
    }
    else
    {
        throw Map::WrongIndexException("Cant access the coords.");
    }
}
