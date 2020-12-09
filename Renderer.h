/**
 * @file Renderer.h
 * 
 * @class Renderer
 * 
 * @author BDFANS
 * 
 * @brief The abstract virtual class used as the base interface for all maprendering classes
 * 
 * @version 0.9.0
 * 
 * @date 2020-12-06
 * 
 */
#pragma once


//to resolve crossreferncing
class Game; 
class Renderer
{

public:

    /**
     * @brief The interface function used to render the specified game instanse
     * 
     * @param ingame the game instance being rendered.
     * 
     */
    virtual void render(const Game& ingame) const =0;

    ///virtual destructor for futureproofing
    virtual ~Renderer() {}
};