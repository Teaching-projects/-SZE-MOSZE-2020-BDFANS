#pragma once

#include "SVGRenderer.h"
#include "Game.h"

class ObserverSVGRenderer : public SVGRenderer
{

public:
    void render(const Game& ingame) const;

    ObserverSVGRenderer(std::string ofilename) :SVGRenderer(ofilename) {};

};