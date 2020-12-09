
#include "PreparedGame.h"
#include "MarkedMap.h"
#include "JSON.h"

PreparedGame::PreparedGame(std::string jsongame) {
	JSON data = JSON::parseFromFile(jsongame); 
	std::string mapfnev = data.get<std::string>("map");
	MarkedMap map(mapfnev);
	setMap(map);
	if(data.count("free_texture") > 0)
	Game::setFreeTexture(data.get<std::string>("free_texture"));
	else {}
	if(data.count("wall_texture") > 0)
	Game::setWallTexture(data.get<std::string>("wall_texture"));
	else {}

	std::string herofnev = data.get<std::string>("hero");
	Hero gamehero = Hero::parse(herofnev);
	std::pair<int, int> hero_location = map.getHeroPosition();
	putHero(gamehero, hero_location.first, hero_location.second);

	int monsterdb = 0;
	while (true) {
		std::string akt = "monster-" + std::to_string(monsterdb + 1);
		if (data.count(akt)) {
			monsterdb++;
		}
		else break;
	}

	std::string aktmfnev;

	for (int i = 0; i < monsterdb; i++) {
		aktmfnev = data.get<std::string>("monster-" + std::to_string(i + 1));
		Monster monster = Monster::parse(aktmfnev);
		std::list<std::pair<int, int>> monster_locations;
		monster_locations = map.getMonsterPositions((char)(i + '1'));

		for (auto j = monster_locations.begin(); j != monster_locations.end(); j++) {
			putMonster(monster, j->first, j->second);
		}
	}
}

void PreparedGame::runGame() {
	Game::run();
}

void PreparedGame::registerRenderer(Renderer* inrender)
{
	Game::registerRenderer(inrender);
}