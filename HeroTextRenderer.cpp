#include "HeroTextRenderer.h"

void HeroTextRenderer::render(const Game& ingame) const
{
    const int& width = ingame.getmap().getlenX();
	const int& height = ingame.getmap().getlenY();
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
	
	out_stream << TOP_LEFT; for (int i = xmin; i < xmax; i++) out_stream << HORIZONTAL; out_stream << TOP_RIGHT << "\n";

	for (int i = ymin; i < ymax; i++) {
		out_stream << VERTICAL;
		for (int j = xmin; j < xmax; j++) {
			try {
				if (ingame.getmap().get(j, i) == type::Wall) out_stream << WALL;
				else if (ingame.getHero() != nullptr && hero_location.first == j && hero_location.second == i) out_stream << HERO;
				else {
					int monstercount = ingame.getMonsterCountOnOnePos(j, i);
					if (monstercount == 1) out_stream << SINGLEMONSTER;
					else if (monstercount > 1) out_stream << MULTIPLEMONSTERS;
					else out_stream << FREE;
				}
			}
			catch (Map::WrongIndexException& e) { out_stream << WALL; }
		}
		out_stream << VERTICAL << "\n";
	}
	out_stream << BOTTOM_LEFT; for (int i = xmin; i < xmax; i++) out_stream << HORIZONTAL; out_stream << BOTTOM_RIGHT << "\n";
}