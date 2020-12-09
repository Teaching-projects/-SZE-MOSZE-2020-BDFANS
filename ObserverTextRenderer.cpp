#include "ObserverTextRenderer.h"

void ObserverTextRenderer::render(const Game& ingame) const
{
    const int& width = ingame.getmap().getlenX();
	const int& heigth = ingame.getmap().getlenY();
    const std::pair<int, int>& hero_location = ingame.getHeroPos();

	out_stream << TOP_LEFT ; for (int i = 0; i < width; i++) out_stream << HORIZONTAL; out_stream << TOP_RIGHT << "\n";

	for (int i = 0; i < heigth; i++) {
		out_stream << VERTICAL;
		for (int j = 0; j < width; j++) {
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

	out_stream << BOTTOM_LEFT; for (int i = 0; i < width; i++) out_stream << HORIZONTAL; out_stream << BOTTOM_RIGHT << "\n";
}