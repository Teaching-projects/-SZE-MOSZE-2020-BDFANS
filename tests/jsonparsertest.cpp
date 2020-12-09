#include "../JSON.h"
#include "../Damage.h"
#include "../Hero.h"
#include "../Monster.h"
#include "../Map.h"
#include "../MarkedMap.h"
#include <gtest/gtest.h>
#include <iostream>
#include <map>

#include "../PreparedGame.h"
#include "../HeroTextRenderer.h"
#include "../ObserverTextRenderer.h"
#include "../CharacterSVGRenderer.h"
#include "../ObserverSVGRenderer.h"

std::map<std::string, JSONDATA> make_compmap()
{
	std::map<std::string, JSONDATA> comp;
	comp.insert({ "str1", "test" });
	comp.insert({ "int1", 2 });
	comp.insert({ "int2", 3.3 });
	comp.insert({ "str2", "tset" });

	return comp;
}
//fileparser tests
//normal fileparse test
TEST(Fileparser, fileparse) {
	std::map<std::string, JSONDATA> comp = make_compmap();
	ASSERT_EQ(JSON::parseFromFile("parsertestfiles/jsonparsertest.txt"), comp);
}

//file with no whitespaces
TEST(Fileparser, no_whitespaces) {
	std::map<std::string, JSONDATA> comp = make_compmap();
	ASSERT_EQ(JSON::parseFromFile("parsertestfiles/nowhitespace.txt"), comp);
}

//file with many whitespaces
TEST(Fileparser, many_whitespaces) {
	std::map<std::string, JSONDATA> comp = make_compmap();
	ASSERT_EQ(JSON::parseFromFile("parsertestfiles/manywhitespace.txt"), comp);
}

//non JSON file
TEST(Fileparser, invalid_file) {
	ASSERT_THROW(JSON::parseFromFile("parsertestfiles/invalidfile.txt"), JSON::ParseException);
}

//stringparser tests
//stringparseing test
TEST(Stringparser, stringparse) {
	std::string instring = "{	\"str1\" : \"test\", \"int1\" : 2, \"int2\" : 3.3, \"str2\" : \"tset\" }";
	std::map<std::string, JSONDATA> comp = make_compmap();
	ASSERT_EQ(JSON::jsonparse_s(instring), comp);
}

//arraytest(String)
TEST(Stringparser, arrayparse)
{
	std::string instring = "{	\"str1\" : \"test\", \"int1\" : 2, \"int2\" : 3.3, \"str2\" : \"tset\", \"array\" : [ \"a\", \"b\", \"c\" ] }";
	std::map<std::string, JSONDATA> comp = make_compmap();
	JSON::list comparray;
	comparray.push_back("a");
	comparray.push_back("b");
	comparray.push_back("c");
	comp.insert({ "array",comparray });
	ASSERT_EQ(JSON::jsonparse_s(instring), comp);
}

//arraytest(int)
TEST(Stringparser, numberarrayparse)
{
	std::string instring = "{	\"str1\" : \"test\", \"int1\" : 2, \"int2\" : 3.3, \"str2\" : \"tset\", \"array\" : [ 1, 2, 3 ] }";
	std::map<std::string, JSONDATA> comp = make_compmap();
	JSON::list comparray;
	comparray.push_back(1);
	comparray.push_back(2);
	comparray.push_back(3);
	comp.insert({ "array",comparray });
	ASSERT_EQ(JSON::jsonparse_s(instring), comp);
}

//Error tests
//broken JSON keyformat
TEST(Parsingerror, broken_input) {
	std::string instring = "{	3 \"str1\" : \"test\", \"int1\" : 2, \"int2\" : 3, \"str2\" : \"tset\" }";

	EXPECT_THROW(JSON::jsonparse_s(instring), JSON::ParseException);

	instring = "{	\"str1\" : \"test\", \"int1\" % 2, \"int2\" : 3, \"str2\" : \"tset\" }";

	EXPECT_THROW(JSON::jsonparse_s(instring), JSON::ParseException);
	
	instring = "{	\"str1\" : \"test\", \"int1\" : 2two, \"int2\" : 3, \"str2\" : \"tset\" }";

	EXPECT_THROW(JSON::jsonparse_s(instring), JSON::ParseException);
	
	instring = "{	\"str1\" : \"test\", \"int1\" : 2, \"int2\" : 3.3.3, \"str2\" : \"tset\" }";

	EXPECT_THROW(JSON::jsonparse_s(instring), JSON::ParseException);
	
	instring = "{	\"str1\" : \"test\", \"int1\" : 2, \"int2\" : 3.3, \"str2\" : \"tset\", \"array\" :  \"a\", \"b\", \"c\" ] }";

	EXPECT_THROW(JSON::jsonparse_s(instring), JSON::ParseException);
	
	instring = "{	\"str1\" : \"test\", \"int1\" : 2, \"int2\" : 3.3, \"str2\" : \"tset\", \"array\" : [ \"a\", \"b\", \"c\"  }";

	EXPECT_THROW(JSON::jsonparse_s(instring), JSON::ParseException);
}


//key in array error
TEST(parsingerror, key_in_array)
{
	std::string instring = "{	\"str1\" : \"test\", \"int1\" : 2, \"int2\" : 3.3, \"str2\" : \"tset\", \"array\" : [ \"a\", \"arraykey\" : \"b\", \"c\" ] }";

	ASSERT_THROW(JSON::jsonparse_s(instring), JSON::ParseException);
}

//Monster tests
//constructor
TEST(Monster, constructorNgettest) {
	Monster a = Monster("a", 4, 3, 7, 4, 2, "example");
	EXPECT_EQ(a.getName(), "a");
	EXPECT_EQ(a.getMaxHealthPoints(), 4);
	EXPECT_EQ(a.getHealthPoints(), 4);
	EXPECT_EQ(a.getPhysicalDamage(), 3);
	EXPECT_EQ(a.getMagicalDamage(), 7);
	EXPECT_EQ(a.getDefense(), 4);
	EXPECT_EQ(a.getAttackCoolDown(), 2);
	EXPECT_EQ(a.getTexture(), "example");
}

//attack tests
//attackdc test
TEST(Attacktest, attackcd) {
	Monster a = Monster("a", 10, 0, 1, 0, 1, "");
	Monster h = Monster("h", 10, 0, 1, 0, 10, "");
	Unit::attackcd(h, a);
	EXPECT_EQ(h.getHealthPoints(), 9);
	EXPECT_EQ(a.getHealthPoints(), 10);
}

//Defense and damage test
TEST(Attacktest, DefensenDamage) {
	Monster a = Monster("a", 10, 101, 0, 100, 1, "");
	Monster h = Monster("h", 10, 0, 8, 100, 1, "");
	Unit::attackcd(h, a);
	EXPECT_EQ(h.getHealthPoints(), 10);
	EXPECT_EQ(a.getHealthPoints(), 2);
	Unit::attackcd(a, h);
	EXPECT_EQ(h.getHealthPoints(), 9);
	EXPECT_EQ(a.getHealthPoints(), 2);
	Monster c = Monster("c", 10, 100, 0, 100, 1, "");
	Unit::attackcd(c, a);
	EXPECT_EQ(a.getHealthPoints(), 2);

}

//hero tests
//constructor
TEST(Hero, constructorNgettest) {
	Hero h = Hero("h", 4, 3, 2, 5, 2, "test", 3, 2, 3, 0, 0, 0.2, 2, 1);
	EXPECT_EQ(h.getName(), "h");
	EXPECT_EQ(h.getMaxHealthPoints(), 4);
	EXPECT_EQ(h.getHealthPoints(), 4);
	EXPECT_EQ(h.getPhysicalDamage(), 3);
	EXPECT_EQ(h.getMagicalDamage(), 2);
	EXPECT_EQ(h.getDefense(), 5);
	EXPECT_EQ(h.getAttackCoolDown(), 2);
	EXPECT_EQ(h.getLevel(), 1);
	EXPECT_EQ(h.getTexture(), "test");
	EXPECT_EQ(h.getExp(), 0);
	EXPECT_EQ(h.getLightRadius(), 2);
}

//XP gain test
TEST(Hero, xpGain) {
	Monster a = Monster("a", 3, 1, 0, 0, 1, "");
	Hero h = Hero("h", 10, 5, 0, 0, 1, "", 100);
	h.attack(a);
	EXPECT_EQ(h.getExp(), 3);
}

//fighttildeath test
TEST(Hero, fightildeath) {
	Monster a = Monster("a", 10, 1, 0, 0, 1, "");
	Hero h = Hero("h", 10, 2, 0, 0, 1, "", 100);
	h.fightTilDeath(a);
	EXPECT_EQ(h.isAlive(), true);
	EXPECT_EQ(a.isAlive(), false);
}

//lvlup test
TEST(Hero, lvlup) {
	Monster a = Monster("a", 13, 1, 0, 0, 4, "");
	Hero h = Hero("h", 10, 1, 0, 0, 2, "", 7, 2, 2, 2, 3, 0.3, 1, 3);
	h.fightTilDeath(a);
	EXPECT_EQ(h.getLevel(), 2);
	EXPECT_EQ(h.getMaxHealthPoints(), 12);
	EXPECT_EQ(h.getPhysicalDamage(), 3);
	EXPECT_EQ(h.getExp(), 6);
	EXPECT_EQ(h.getAttackCoolDown(), 2 * 0.3);
	EXPECT_EQ(h.getMagicalDamage(), 2);
	EXPECT_EQ(h.getDefense(), 3);
	EXPECT_EQ(h.getLightRadius(), 4);
}

//Map test
//constructor
TEST(Map, constructorNgettest) {
	Map test = Map("maptestfiles/Testmap.txt");
	EXPECT_EQ(test.getlenX(), 14);
	EXPECT_EQ(test.getlenY(), 7);

	std::string expected = "##############\n";
	expected += "#   #  ####  #\n";
	expected += "# ####  ##  ##\n";
	expected += "#   #  ##  ###\n";
	expected += "### # ##  ####\n";
	expected += "#        #####\n";
	expected += "##############\n";


	std::string output;

	for (int i = 0; i < test.getlenY(); i++)
	{
		for (int j = 0; j < test.getlenX(); j++)
		{
			switch (test.get(j, i))
			{
			case Free:
				output += ' ';
				break;
			case Wall:
				output += '#';
				break;
			}
		}
		output += '\n';
	}
	EXPECT_EQ(expected, output);
}

//get exception
TEST(Map, WrongIndexException) {
	Map test = Map("maptestfiles/Testmap.txt");
	EXPECT_EQ(test.getlenX(), 14);
	EXPECT_EQ(test.getlenY(), 7);

	ASSERT_THROW(test.get(10, 30), Map::WrongIndexException);

}

//MarkedMap test
//constructor
TEST(MarkedMap, constructorNgettest) {
	MarkedMap test = MarkedMap("maptestfiles/MTestmap.txt");
	EXPECT_EQ(test.getlenX(), 14);
	EXPECT_EQ(test.getlenY(), 7);

	std::string expected = "##############\n";
	expected += "#   #  ####  #\n";
	expected += "# ####  ##  ##\n";
	expected += "#   #  ##  ###\n";
	expected += "### # ##  ####\n";
	expected += "#         ####\n";
	expected += "##############\n";


	std::string output;

	for (int i = 0; i < test.getlenY(); i++)
	{
		for (int j = 0; j < test.getlenX(); j++)
		{
			switch (test.get(j, i))
			{
			case Free:
				output += ' ';
				break;
			case Wall:
				output += '#';
				break;
			}
		}
		output += '\n';
	}
	EXPECT_EQ(expected, output);
}

//getposition tests
TEST(MarkedMap, getpositions) {
	MarkedMap test = MarkedMap("maptestfiles/MTestmap.txt");
	EXPECT_EQ(test.getHeroPosition(), std::make_pair(2, 1));
	std::list<std::pair<int, int>> m1, m2, m3;
	m1.push_back(std::make_pair(2, 3));
	m1.push_back(std::make_pair(3, 4));
	m1.push_back(std::make_pair(6, 5));
	EXPECT_EQ(test.getMonsterPositions('1'), m1);
	m2.push_back(std::make_pair(6, 2));
	m2.push_back(std::make_pair(7, 2));
	m2.push_back(std::make_pair(3, 3));
	EXPECT_EQ(test.getMonsterPositions('2'), m2);
	m3.push_back(std::make_pair(6, 3));
	EXPECT_EQ(test.getMonsterPositions('3'), m3);
}

//exception tests
TEST(MarkedMap, exceptions) {
	MarkedMap test = MarkedMap("maptestfiles/Testmap.txt");
	EXPECT_THROW(test.getHeroPosition(), MarkedMap::NoInstanceException);
	EXPECT_THROW(test.getMonsterPositions('6'), MarkedMap::NoInstanceException);
	EXPECT_THROW(test.loadMap("maptestfiles/MTestmapHeroes.txt"), MarkedMap::MultipleHeroException);
}

//Game tests
//constructor, getter functions, put functions and exception detections
TEST(Game, constructNgetNputtests) {
	Game test = Game();
	EXPECT_EQ(test.getHero(), nullptr);
	EXPECT_EQ(test.getHeroPos().first, 0);
	EXPECT_EQ(test.getHeroPos().second, 0);
	EXPECT_THROW(test.putHero(Hero("h", 10, 5, 0, 0, 1, ""), 0, 0), Map::WrongIndexException);
	EXPECT_THROW(test.putMonster(Monster::parse("Zombie.json"), 3, 5), Map::WrongIndexException);
	test.setFreeTexture("freed");
	EXPECT_EQ(test.getFreeTexture(), "freed");
	test.setWallTexture("walled");
	EXPECT_EQ(test.getWallTexture(), "walled");

	std::string filename = "maptestfiles/Testmap.txt";
	Game test2 = Game(filename);
	EXPECT_THROW(test2.run(), Game::NotInitializedException);
	EXPECT_THROW(test2.putHero(Hero("h", 10, 5, 0, 0, 1, ""), 0, 0), Game::OccupiedException);
	EXPECT_NO_THROW(test2.putHero(Hero("h", 10, 5, 0, 0, 1, ""), 1, 2));
	EXPECT_EQ(test2.getHeroPos().first, 1);
	EXPECT_EQ(test2.getHeroPos().second, 2);
	EXPECT_THROW(test2.putHero(Hero("h", 10, 5, 0, 0, 1, ""), 1, 1), Game::AlreadyHasHeroException);
	EXPECT_THROW(test2.putMonster(Monster::parse("Zombie.json"), 0, 0), Game::OccupiedException);
	EXPECT_THROW(test2.putMonster(Monster::parse("Zombie.json"), 1, 2), Game::OccupiedException);
	EXPECT_NO_THROW(test2.putMonster(Monster::parse("Zombie.json"), 2, 1));
	EXPECT_NO_THROW(test2.putMonster(Monster::parse("Zombie.json"), 2, 1));
	EXPECT_NO_THROW(test2.putMonster(Monster::parse("Fallen.json"), 2, 1));
	EXPECT_NO_THROW(test2.putMonster(Monster::parse("Fallen.json"), 3, 1));
}

//Testing monstercounting
TEST(Game, monstercounttest) {
	
	std::string filename = "maptestfiles/Testmap.txt";
	Game test2 = Game(filename);
	EXPECT_EQ(test2.getMonsterCountOnOnePos(1, 1), 0);
	test2.putMonster(Monster::parse("Zombie.json"), 1, 1);
	EXPECT_EQ(test2.getMonsterCountOnOnePos(1, 1), 1);
	test2.putMonster(Monster::parse("Fallen.json"), 1, 1);
	EXPECT_EQ(test2.getMonsterCountOnOnePos(1, 1), 2);
}

//Gametests
//run and render test
TEST(Game, runNrendertest) {
	std::string filename = "maptestfiles/Testmap.txt";
	Game test2 = Game(filename);
	test2.putHero(Hero::parse("Dark_Wanderer.json"), 1, 2);
	test2.putMonster(Monster::parse("Zombie.json"), 2, 1);
	test2.putMonster(Monster::parse("Zombie.json"), 2, 1);
	test2.putMonster(Monster::parse("Fallen.json"), 2, 1);
	test2.putMonster(Monster::parse("Fallen.json"), 3, 1);
	test2.setWallTexture("wall.svg");
	test2.setFreeTexture("free.svg");

	test2.registerRenderer(new HeroTextRenderer());
	test2.registerRenderer(new HeroTextRenderer());

	std::ofstream intxt("testlog.txt");
	test2.registerRenderer(new ObserverTextRenderer(intxt));
	test2.registerRenderer(new CharacterSVGRenderer("testpretty.svg"));
	test2.registerRenderer(new ObserverSVGRenderer("testgamemaster.svg"));
	
	std::ifstream in("gameinputs/gametestmove.txt");
	std::streambuf* cinbuf = std::cin.rdbuf();
	std::cin.rdbuf(in.rdbuf());

	std::ofstream out("couttext.txt");
	std::streambuf* coutbuf = std::cout.rdbuf();
	std::cout.rdbuf(out.rdbuf());


	EXPECT_NO_THROW(test2.run());
	std::cin.rdbuf(cinbuf);
	std::cout.rdbuf(coutbuf);


	std::ifstream filecomp1, filecomp2;
	char comp1, comp2;
	ASSERT_NO_THROW(filecomp1.open("couttext.txt"));
	ASSERT_NO_THROW(filecomp2.open("renderertestfiles/couttextcompare.txt"));
	while (!filecomp1.get(comp1) && !filecomp2.get(comp2))
	{
		EXPECT_EQ(comp1, comp2);
	}
	filecomp1.close(); 
	filecomp2.close();
	ASSERT_NO_THROW(filecomp1.open("testlog.txt"));
	ASSERT_NO_THROW(filecomp2.open("renderertestfiles/logcompare.txt"));
	while (!filecomp1.get(comp1) && !filecomp2.get(comp2))
	{
		EXPECT_EQ(comp1, comp2);
	}
	filecomp1.close();
	filecomp2.close();
	ASSERT_NO_THROW(filecomp1.open("testpretty.svg"));
	ASSERT_NO_THROW(filecomp2.open("renderertestfiles/prettycompare.svg"));
	while (!filecomp1.get(comp1) && !filecomp2.get(comp2))
	{
		EXPECT_EQ(comp1, comp2);
	}
	filecomp1.close();
	filecomp2.close();
	ASSERT_NO_THROW(filecomp1.open("testgamemaster.svg"));
	ASSERT_NO_THROW(filecomp2.open("renderertestfiles/gamemastercompare.svg"));
	while (!filecomp1.get(comp1) && !filecomp2.get(comp2))
	{
		EXPECT_EQ(comp1, comp2);
	}
	filecomp1.close();
	filecomp2.close();
}

//PreparedGame
//Construct
TEST(PreparedGame, construct)
{
	std::string filename = "preparedgame.json";
	PreparedGame game = PreparedGame(filename);
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}


