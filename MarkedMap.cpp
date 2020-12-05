#include "MarkedMap.h"

#include <fstream>
#include <string>
#include <algorithm>


    std::pair<int,int> MarkedMap::getHeroPosition() const
    {
        if(hero_pos.first < 0 && hero_pos.second < 0 )
        {
            throw NoInstanceException("Warning! no instance of hero was found");
        }
        else
        {
            return hero_pos;
        }
    }

    std::list<std::pair<int,int>> MarkedMap::getMonsterPositions(char c) const
    {
        if(monster_pos.count(c) > 0)
        {
        return monster_pos.find(c)->second;
        }
        else
        {
            throw NoInstanceException("Warning! no instance of monster was found!\n");
        }
        
    }

    void MarkedMap::loadMap(std::string filename)
    {
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
        }
        lenX = inX;
        lenY = inY;
        loadedmap = MAPMATRIX(lenY, std::vector<type>(lenX, type::Wall));

        //load map features
        infile.clear();
        infile.seekg(0);
        inY = 0;
        bool has_hero = false;
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

                case 'H':
                    if(has_hero)
                    {
                        throw MultipleHeroException("Error! More than one instance of hero was found!\n");
                    }
                    else
                    {
                        has_hero = true;
                        hero_pos = std::make_pair(inX,inY);
                        loadedmap[inY][inX] = type::Free;
                    }
                    
                    break;

                default:
                    if(instring[inX] >= '0' && instring[inX] <= '9')
                    {
                        if(monster_pos.count(instring[inX]) > 0)
                        {
                            monster_pos.find(instring[inX])->second.push_back(std::make_pair(inX,inY));
                        }
                        else
                        {    
                            monster_pos.insert(std::make_pair(instring[inX],std::list<std::pair<int,int>>(1,std::make_pair(inX,inY))));
                        }
                        loadedmap[inY][inX] = type::Free;
                    }
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