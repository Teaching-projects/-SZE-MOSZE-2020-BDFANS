
#include "Game.h"

Game::Game(std::string mapfilenev) :hero(), isMapSet(false), isHeroSet(false), isMonsterSet(false), isStarted(false), {

	Map newMap(mapfilenev);
	setMap(newMap);
}


void Game::setMap(Map map) {
	if (!isStarted) {
		if (!isHeroSet and !isMonsterSet) {

			newMap = map;
			isMapSet = true;

		}else throw AlreadyHasUnitException("We have units on the map. Can not change map.");
	}else throw GameAlreadyStartedException("The game is running. Can not change map.");
}

void Game::putHero(Hero hero, int x, int y) {
	if (!isHeroSet) {
		if (isMapSet) {
			if (!isStarted) {
				if (newMap.get(x, y) == Map::type::Free) {

					h_location = std::make_pair(x, y);
					hero = new Hero(hero);
					isHeroSet = true;

				}else throw OccupiedException("Can't put a hero to this position.");
			}else throw GameAlreadyStartedException("You can't put down a hero while the game is running.");
		}else throw Map::WrongIndexException("Map is not initialized! Please initialize the map first.");
	}else throw AlreadyHasHeroException("Initializing second hero is not possible.");
}

void Game::putMonster(Monster monster, int x, int y) {
	if (isMapSet) {
		if (newMap.get(x, y) == Map::type::Free) {

			m_locations.push_back(std::make_pair(monster, std::make_pair(x, y)));
			isMonsterSet = true;

		}else throw OccupiedException("Can't put a monster to this position.");
	}else throw Map::WrongIndexException("Map is not initialized! Please initialize the map first.");
}

void Game::run() {
	if (isMapSet and isHeroSet and isMonsterSet) {
		isStarted = true;
		while (hero->isAlive() && !m_locations.empty()) {
			std::string input = "";
			isStarted = true;
			Game::showMap();
			std::cout << "Please enter where do u want to go (east, north, west, south): ";
			std::getline(cin, input);
			std::cout << std::endl;
			if (Game::stepOn(input)) {
				if (getMonsterCountOnOnePos(h_location.first, h_location.second) > 0) {
					auto i = m_locations.begin();
					while (i != m_locations.end() && !m_locations.empty()) {
						if (i->second.first == h_location.first && i->second.second == h_location.second) {
							hero->fightTilDeath(i->first);
							if (hero->isAlive()) {
								i = m_locations.erase(i);
							}
						}
						else i++;
					}
				}
			}
		}
		if (m_locations.empty()) std::cout << hero->getName() << " cleared the map." << std::endl;
		else std::cout << "The hero died." << std::endl;
	} else throw NotInitializedException("Can't start the game.") << std::endl ;
}


int Game::stepOn(std::string command) {
	bool ok = true;
	if (command=="west" && newMap.get(h_location.first-1, h_location.second)==Map::type::Free){
		h_location.first -= 1;
	}else if (command == "east" && newMap.get(h_location.first + 1, h_location.second) == Map::type::Free) {
		h_location.first += 1;
	}else if (command == "north" && newMap.get(h_location.first, h_location.second - 1) == Map::type::Free) {
		h_location.second -= 1;
	}else if (command == "south" && newMap.get(h_location.first, h_location.second + 1) == Map::type::Free) {
		h_location.first += 1;
	}
	else { ok = false; }

	return ok;
}


int Game::getMonsterCountOnOnePos(int x, int y) const
{
	int db = 0;
	for (auto i = m_locations.begin(); i != m_locations.end(); i++) {
		if (i->second.first == x && i->second.second == y) {
			db++;
		}
	}
	return db;
}



void Game::showMap() {
	int width = newMap.getMapWidth();
	int heigth = newMap.getMapHeigth();

	std::cout << "|"; for (int i = 0; i < width; i++) std::cout << "--"; std::cout << "|" << std::endl;

	for (int i = 0; i < heigth; i++) {
		std::cout << "|";
		for (int j = 0; j < width; j++) {
			try {
				if (newMap.get(j, i) == Map::type::Wall) std::cout << "#";
				else if ((hero.posy == i) and (hero.posx == j)) std::cout << "H";
				else {
					int monstercount = getMonsterCountOnOnePos(j, i);
					if (monstercount == 1) std::cout << "M";
					else if (monstercount > 1) std::cout << "MM";
					else std::cout << " ";
				}
			}
			catch (Map::WrongIndexException& e) { std::cout << "#"; }
		}
		std::cout << "|\n";
	}

	std::cout << "|"; for (int i = 0; i < width; i++) std::cout << "__"; std::cout << "|" << std::endl;
}