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
#include "PreparedGame.h"

#include <fstream>

#include "HeroTextRenderer.h"
#include "ObserverTextRenderer.h"
#include "ObserverSVGRenderer.h"
#include "CharacterSVGRenderer.h"



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

    try {
        PreparedGame game = PreparedGame(argv[1]);
        
        game.registerRenderer(new HeroTextRenderer());  

        std::ofstream in("log.txt");
        game.registerRenderer(new ObserverTextRenderer(in));

        game.registerRenderer(new CharacterSVGRenderer("pretty.svg"));

        game.registerRenderer(new ObserverSVGRenderer("gamemaster.svg"));

        game.runGame();
    }
    catch (const JSON::ParseException& e) { bad_exit(4); }

    return 0;
}
