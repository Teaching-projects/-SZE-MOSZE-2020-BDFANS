#pragma once

#include "SVGRenderer.h"
#include "Game.h"

class ObserverSVGRenderer : public SVGRenderer
{

public:
    void render(const Game& ingame) const override;

    explicit ObserverSVGRenderer(const std::string& ofilename) :SVGRenderer(ofilename) {};

};