
#include "PreparedGame.h"
#include "MarkedMap.h"
#include "JSON.h"

PreparedGame::PreparedGame(std::string jsongame) {
	JSON data = JSON::parseFromFile(jsongame); 
	std::string mapfnev = data.get<std::string>("map");
	MarkedMap map(mapfnev);
	setMap(map);

	std::string herofnev = data.get<std::string>("hero");
	Hero gamehero = Hero::parse(herofnev);
	std::pair<int, int> hero_location = map.getHeroPosition();
	putHero(gamehero, hero_location.first, hero_location.second);

	std::string monsterfnev = data.get<std::string>("monster");
	Monster monster = Monster::parse(monsterfnev);
	int monsterdb = 0;
	while (true) {
		std::string akt = "monster-" + std::to_string(monsterdb + 1);
		if (data.count(akt)) {
			monsterdb++;
		}
		else break;
	}

	std::string aktmfnev="";

	for (int i = 0; i < monsterdb; i++) {
		aktmfnev = json.get<std::string>("monster-" + std::to_string(i + 1));
		Monster monster = Monster::parse(aktmfnev);
		std::list<std::pair<int, int>> monster_locations;
		monster_locations = map.getMonsterPositions((char)(i + '1'));

		for (auto i = monster_locations.begin(); i != monster_locations.end(); i++) {
			putMonster(monster, i->first, i->second);
		}
	}
}