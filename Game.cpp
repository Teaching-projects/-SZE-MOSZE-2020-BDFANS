
#include "Game.h"


void Game::setMap(Map map) {
	if (!isStarted) {
		if (!isHeroSet && !isMonsterSet) {
	
			newMap = map;
			isMapSet = true;

		}else throw AlreadyHasUnitException("We have units on the map. Can not change map.");
	}else throw GameAlreadyStartedException("The game is running. Can not change map.");
}

void Game::putHero(Hero hero, int x, int y) {
	if (!isHeroSet) {
		if (isMapSet) {
			if (!isStarted) {
				if (newMap.get(x, y) == type::Free) {

					gamehero = new Hero(hero);
					h_location = std::make_pair(x, y);
					isHeroSet = true;

				}else throw OccupiedException("Can't put a hero to this position.");
			}else throw GameAlreadyStartedException("You can't put down a hero while the game is running.");
		}else throw Map::WrongIndexException("Map is not initialized! Please initialize the map first.");
	}else throw AlreadyHasHeroException("Initializing second hero is not possible.");
}

void Game::putMonster(Monster monster, int x, int y) {
	if (isMapSet) {
		if (newMap.get(x, y) == type::Free) {

			m_locations.push_back(std::make_pair(monster, std::make_pair(x, y)));
			isMonsterSet = true;

		}else throw OccupiedException("Can't put a monster to this position.");
	}else throw Map::WrongIndexException("Map is not initialized! Please initialize the map first.");
}

void Game::run() {
	if (isMapSet && isHeroSet && isMonsterSet) {
		isStarted = true;
		while (gamehero->isAlive() && !m_locations.empty()) {
			std::string input = "";
			Game::showHeroVision();
			std::cout << "Please enter where do u want to go (east, north, west, south): ";
			std::getline(std::cin, input);
			std::cout << std::endl;
			if (Game::stepOn(input)) {
				Game::showHeroVision();
				if (getMonsterCountOnOnePos(h_location.first, h_location.second) > 0) {
					auto i = m_locations.begin();
					while (i != m_locations.end() && !m_locations.empty() && gamehero->isAlive()) {
						if (i->second.first == h_location.first && i->second.second == h_location.second) {
							gamehero->fightTilDeath(i->first);
							if (gamehero->isAlive()) {
								i = m_locations.erase(i);
							}
						}
						else i++;
					}
				}
			}
		}
		if (m_locations.empty()) std::cout << gamehero->getName() << " cleared the map." << std::endl;
		else std::cout << "The hero died." << std::endl;
		isStarted = false;
	} else throw NotInitializedException("Can't start the game.");
}


bool Game::stepOn(std::string command) {
	bool ok = true;
	int x = h_location.first;
	int y = h_location.second;

	if (command=="west" && heroIsOnMap(x - 1, y) && newMap.get(x - 1, y) == type::Free){
		h_location.first = x - 1;
	}else if (command == "east" && heroIsOnMap(x + 1, y) && newMap.get(x + 1, y) == type::Free) {
		h_location.first = x + 1;
	}else if (command == "north" && heroIsOnMap(x, y - 1) && newMap.get(x, y - 1) == type::Free) {
		h_location.second = y - 1;
	}else if (command == "south" && heroIsOnMap(x, y + 1) && newMap.get(x, y + 1) == type::Free) {
		h_location.second = y +1;
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

bool Game::heroIsOnMap(int x, int y) {
	bool onMap = false;
	if (x <= newMap.getMapWidth() && y <= newMap.getMapHeigth()) {
		onMap = true;
	}
	else { std::cout << "End of the map. \n"; }

	return onMap;
}


void Game::showMap() {
	int width = newMap.getMapWidth();
	int heigth = newMap.getMapHeigth();

	std::cout << TOP_LEFT ; for (int i = 0; i < width; i++) std::cout << HORIZONTAL; std::cout << TOP_RIGHT << std::endl;

	for (int i = 0; i < heigth; i++) {
		std::cout << VERTICAL;
		for (int j = 0; j < width; j++) {
			try {
				if (newMap.get(j, i) == type::Wall) std::cout << WALL;
				else if (gamehero != nullptr && h_location.first == j && h_location.second == i) std::cout << HERO;
				else {
					int monstercount = getMonsterCountOnOnePos(j, i);
					if (monstercount == 1) std::cout << SINGLEMONSTER;
					else if (monstercount > 1) std::cout << MULTIPLEMONSTERS;
					else std::cout << FREE;
				}
			}
			catch (Map::WrongIndexException& e) { std::cout << WALL; }
		}
		std::cout << VERTICAL << "\n";
	}

	std::cout << BOTTOM_LEFT; for (int i = 0; i < width; i++) std::cout << HORIZONTAL; std::cout << BOTTOM_RIGHT << std::endl;
}

void Game::showHeroVision() {
	int width = newMap.getMapWidth();
	int height = newMap.getMapHeigth();
	int radius = gamehero->getLightRadius();
	int xmin = h_location.first - radius;
	if (xmin < 0) { xmin = 0; }
	int xmax = h_location.first + radius;
	if (xmax > width) { xmax = width - 1; }
	int ymin = h_location.second - radius;
	if (ymin < 0) { xmin = 0; }
	int ymax = h_location.second + radius;
	if (ymax > height) { ymax = height; }
	
	std::cout << TOP_LEFT; for (int i = xmin; i < xmax; i++) std::cout << HORIZONTAL; std::cout << TOP_RIGHT << std::endl;

	for (int i = xmin; i < xmax; i++) {
		std::cout << VERTICAL;
		for (int j = ymin; j < ymax; j++) {
			try {
				if (newMap.get(j, i) == type::Wall) std::cout << WALL;
				else if (gamehero != nullptr && h_location.first == j && h_location.second == i) std::cout << HERO;
				else {
					int monstercount = getMonsterCountOnOnePos(j, i);
					if (monstercount == 1) std::cout << SINGLEMONSTER;
					else if (monstercount > 1) std::cout << MULTIPLEMONSTERS;
					else std::cout << FREE;
				}
			}
			catch (Map::WrongIndexException& e) { std::cout << WALL; }
		}
		std::cout << VERTICAL << "\n";
	}
	std::cout << BOTTOM_LEFT; for (int i = xmin; i < xmax; i++) std::cout << HORIZONTAL; std::cout << BOTTOM_RIGHT << std::endl;
}