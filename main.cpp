#include <iostream>
#include <map>
#include <string>
#include <filesystem>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <list>

#include "JSON.h"
#include "Damage.h"
#include "Hero.h"
#include "Monster.h"
#include "Game.h"




const std::map<int,std::string> error_messages = {
    { 1 , "Bad number of arguments. Only a single scenario file should be provided." },
    { 2 , "The provided scenario file is not accessible." },
    { 3 , "The provided scenario file is invalid." },
    { 4 , "JSON parsing error." }
};

void bad_exit(int exitcode){
    std::cerr 
        << (error_messages.count(exitcode) ? error_messages.at(exitcode) : "Unknown error")
        << std::endl;
    exit(exitcode);
}

int main(int argc, char** argv){
    if (argc != 2) bad_exit(1);
    if (!std::filesystem::exists(argv[1])) bad_exit(2);

    std::string hero_file;
    std::list<std::string> monster_files;
    try {
        JSON scenario = JSON::parseFromFile(argv[1]); 
        if (!(scenario.count("hero")&&scenario.count("monsters"))) bad_exit(3);
        else {
            hero_file=scenario.get<std::string>("hero");
            std::istringstream monsters(scenario.get<std::string>("monsters"));
            std::copy(std::istream_iterator<std::string>(monsters),
                std::istream_iterator<std::string>(),
                std::back_inserter(monster_files));
        }
    } catch (const JSON::ParseException& e) {bad_exit(4);}

    try { 
        Hero hero{Hero::parse(hero_file)};
        std::list<Monster> monsters;
        for (const auto& monster_file : monster_files)
            monsters.push_back(Monster::parse(monster_file));        

        while (hero.isAlive() && !monsters.empty()) {
            std::cout 
                << hero.getName() << "(" << hero.getLevel()<<")"
                << " vs "
                << monsters.front().getName()
                <<std::endl;
            hero.fightTilDeath(monsters.front());
            if (!monsters.front().isAlive()) monsters.pop_front();
        }
        std::cout << (hero.isAlive() ? "The hero won." : "The hero died.") << std::endl;
        std::cout << hero.getName() << ": LVL" << hero.getLevel() << std::endl
                  << "   HP: "<<hero.getHealthPoints()<<"/"<<hero.getMaxHealthPoints()<<std::endl
                  << "  DMG: "<<hero.getDamage()<<std::endl
                  << "  ACD: "<<hero.getAttackCoolDown()<<std::endl
                  ;
    } catch (const JSON::ParseException& e) {bad_exit(4);}

    try {
        std::cout << "Please add a map file." << std::endl;
        std::string mapfnev;
        std::getline(std::cin, mapfnev);
        Map map(mapfnev);
        Game game{};
        game.setMap(map);
        std::list <Monster> m_loc;
        Hero hero{ Hero::parse(hero_file) };
        for (const auto& m_file : monster_files) {
            m_loc.push_back(Monster::parse(m_file));
        }
        for (const auto& i : m_loc) {
            std::string x_koord, y_koord;
            game.showMap();
            std::cout << "Give the x coordinate for the monster, " << i.getName() << ": ";
            std::getline(std::cin, x_koord);
            std::cout << std::endl << "The y coordinate: ";
            std::getline(std::cin, y_koord);
            std::cout << std::endl;
            int x = std::stoi(x_koord);
            int y = std::stoi(y_koord);
            game.putMonster(i, x, y);
        }
        game.showMap();
        std::string x_koord, y_koord;
        std::cout << "Give the x coordinate for the hero, " << hero.getName() << ": ";
        std::getline(std::cin, x_koord);
        std::cout << std::endl << "The y coordinate: ";
        std::getline(std::cin, y_koord);
        std::cout << std::endl;
        int x = std::stoi(x_koord);
        int y = std::stoi(y_koord);
        game.putHero(hero, x, y);

        game.run();
    }
    catch (const JSON::ParseException& e) { bad_exit(4); }

    return 0;
}
