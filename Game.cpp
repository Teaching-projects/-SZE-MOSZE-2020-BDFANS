
#include "Game.h"


void Game::setMap(const Map& map) {
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
		if(newMap.get(x, y) == type::Free && !(h_location.first == x && h_location.second == y)) {

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
			Game::renderall();
			std::cout << "Please enter where do u want to go (east, north, west, south): ";
			std::getline(std::cin, input);
			std::cout << std::endl;
			if (Game::stepOn(input)) {
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


bool Game::stepOn(const std::string& command) {
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
	if (x <= newMap.getlenX() && y <= newMap.getlenY()) {
		onMap = true;
	}
	else { std::cout << "End of the map. \n"; }

	return onMap;
}

    void Game::registerRenderer(Renderer* inrender)
	{
		rendererlist.push_back(inrender);
	}
    

    void Game::renderall()
	{
		for(auto& iterator : rendererlist) 
    	{
			iterator->render(*this);
		}
	}

	std::list<Monster> Game::getMonstersonPos(int x, int y) const
	{
		std::pair<int,int> location(x,y);
		std::list<Monster> outlist;
		if(newMap.get(x, y) != type::Wall && location != getHeroPos())
		{
			for (auto i = m_locations.begin(); i != m_locations.end(); i++)
			{
				if(i->second == location)
				{
					outlist.push_back(i->first);
				}
				else {}
			}
		}
		else {}
			
		return outlist;
	}

Game::~Game() 
{
	delete gamehero;

	for(auto&& iterator : rendererlist) 
    {
		delete iterator;
	}
}