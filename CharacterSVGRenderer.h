#pragma once

#include "SVGRenderer.h"
#include "Game.h"

class CharacterSVGRenderer: public SVGRenderer
{

public:

    void render(const Game& ingame) const override;

    CharacterSVGRenderer(std::string ofilename) :SVGRenderer(ofilename) {};
};