/**
 * @file Map.h
 * @class Map
 *
 * @author BDFANS
 *
 * @brief header for Map class
 * @version 0.4.0
 *
 *
 * @date 2020-11-13
 *
 */
#pragma once

#include <iostream>
#include <vector>


#define MAPMATRIX std::vector<std::vector<type>> 

///This enum represents the map features(Free tiles and Walls)
enum type {Free,Wall};

class Map
{

    //The actual map stored in a vector matrix of "type"
    MAPMATRIX loadedmap;
    ///Width of the map
    int lenX;
    ///Length of the map
    int lenY;


public:

    ///The exception thrown when the map is indexed outside of its bounds
    class WrongIndexException :public std::exception {  };

    Map(std::string filename);

    /**
     * @brief Return the type of tile located at the coordinates
     * 
     * @param x the X coordinates
     * @param y the Y coordinates
     * @return type the type of the tile
     */
    type get(int x, int y) const;

    ///return the width of the map
    int getlenX() const
    {
        return lenX;
    }

    ///returns the length of the map
    int getlenY() const
    {
        return lenY;
    }


};