#include "ObserverSVGRenderer.h"

void ObserverSVGRenderer::render(const Game& ingame) const
{
    const int& width = ingame.getmap().getlenX();
	const int& heigth = ingame.getmap().getlenY();
    const std::pair<int, int>& hero_location = ingame.getHeroPos();

    std::ofstream outfile;
    outfile.open(outfilename, std::ofstream::out | std::ofstream::trunc);

    outfile << "<svg width=\"" << std::to_string(width*10) << "\"  height=\"" << std::to_string(heigth*10) << "\" xmlns=\"http://www.w3.org/2000/svg\">\n";

	for (int i = 0; i < heigth; i++) {
		for (int j = 0; j < width; j++) {
			try {
				if (ingame.getmap().get(j, i) == type::Wall) outfile << getImage(ingame.getWallTexture(),j,i);
				else if (ingame.getHero() != nullptr && hero_location.first == j && hero_location.second == i) outfile << getImage(ingame.getHero()->getTexture(),j,i);
				else {
					int monstercount = ingame.getMonsterCountOnOnePos(j, i);
					if (monstercount >= 1) outfile << getImage(ingame.getMonstersonPos(j,i).front().getTexture(),j,i);
					else outfile << getImage(ingame.getFreeTexture(),j,i);
				}
			}
			catch (Map::WrongIndexException& e) { outfile << getImage(ingame.getWallTexture(),j,i); }
		}
	}

    outfile << "</svg>";

    outfile.close();
}