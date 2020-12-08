#include "CharacterSVGRenderer.h"

void CharacterSVGRenderer::render(const Game& ingame) const
{
    const int& width = ingame.getmap().getMapWidth();
	const int& height = ingame.getmap().getMapHeigth();
	int radius = ingame.getHero()->getLightRadius();
    const std::pair<int, int>& hero_location = ingame.getHeroPos();
	int xmin = hero_location.first - radius;
	if (xmin < 0) { xmin = 0; }
	int xmax = hero_location.first + radius + 1;
	if (xmax > width) { xmax = width; }
	int ymin = hero_location.second - radius;
	if (ymin < 0) { ymin = 0; }
	int ymax = hero_location.second + radius + 1;
	if (ymax > height) { ymax = height; }
	
    std::ofstream outfile;
    outfile.open(outfilename, std::ofstream::out | std::ofstream::trunc);

    outfile << "<svg width=\"" << width << "\"  height=\"" << height << "\" xmlns=\"http://www.w3.org/2000/svg\">\n";

	for (int i = ymin; i < ymax; i++) {
		for (int j = xmin; j < xmax; j++) {
			try {
				if (ingame.getmap().get(j, i) == type::Wall) outfile << getImage(ingame.getWallTexture(),j,i);
				else if (ingame.getHero() != nullptr && hero_location.first == j && hero_location.second == i) outfile << getImage(ingame.getHero()->getTexture(),j,i);
				else {
					int monstercount = ingame.getMonsterCountOnOnePos(j, i);
					if (monstercount >= 1) outfile << getImage(ingame.getMonstersonPos(j,i).front().getTexture(),j,i);
					else outfile << getImage(ingame.getFreeTexture(),j,i);
				}
			}
			catch (Map::WrongIndexException& e) { getImage(ingame.getWallTexture(),j,i); }
		}
	}

    outfile << "</svg>";

    outfile.close();
}