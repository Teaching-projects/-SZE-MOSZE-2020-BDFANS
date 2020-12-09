#include "../JSON.h"
#include "../Damage.h"
#include "../Hero.h"
#include "../Monster.h"
#include "../Map.h"
#include "../MarkedMap.h"
#include <gtest/gtest.h>
#include <iostream>
#include <map>


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
TEST(Parsingerror, broken_key) {
	std::string instring = "{	3 \"str1\" : \"test\", \"int1\" : 2, \"int2\" : 3, \"str2\" : \"tset\" }";

	ASSERT_THROW(JSON::jsonparse_s(instring), JSON::ParseException);

}

//broken key/value separator
TEST(Parsingerror, broken_separator) {
	std::string instring = "{	\"str1\" : \"test\", \"int1\" % 2, \"int2\" : 3, \"str2\" : \"tset\" }";

	ASSERT_THROW(JSON::jsonparse_s(instring), JSON::ParseException);

}

//illegal character in number value
TEST(Parsingerror, broken_numvalue) {
	std::string instring = "{	\"str1\" : \"test\", \"int1\" : 2two, \"int2\" : 3, \"str2\" : \"tset\" }";

	ASSERT_THROW(JSON::jsonparse_s(instring), JSON::ParseException);
}

//multiple decimal separator error
TEST(Parsingerror, broken_numvalue_separators) {
	std::string instring = "{	\"str1\" : \"test\", \"int1\" : 2, \"int2\" : 3.3.3, \"str2\" : \"tset\" }";

	ASSERT_THROW(JSON::jsonparse_s(instring), JSON::ParseException);
}

//broken array start
TEST(parsingerror, broken_array_start)
{
	std::string instring = "{	\"str1\" : \"test\", \"int1\" : 2, \"int2\" : 3.3, \"str2\" : \"tset\", \"array\" :  \"a\", \"b\", \"c\" ] }";

	ASSERT_THROW(JSON::jsonparse_s(instring), JSON::ParseException);
}

//broken array end
TEST(parsingerror, broken_array_end)
{
	std::string instring = "{	\"str1\" : \"test\", \"int1\" : 2, \"int2\" : 3.3, \"str2\" : \"tset\", \"array\" : [ \"a\", \"b\", \"c\"  }";

	ASSERT_THROW(JSON::jsonparse_s(instring), JSON::ParseException);
}


//key in array error
TEST(parsingerror, key_in_array)
{
	std::string instring = "{	\"str1\" : \"test\", \"int1\" : 2, \"int2\" : 3.3, \"str2\" : \"tset\", \"array\" : [ \"a\", \"arraykey\" : \"b\", \"c\" ] }";

	ASSERT_THROW(JSON::jsonparse_s(instring), JSON::ParseException);
}

//Monster tests
//constructor
TEST(Monster, constructor) {
	Monster a = Monster("a", 4, 3, 0, 0, 2,"");
	EXPECT_EQ(a.getName(), "a");
	EXPECT_EQ(a.getMaxHealthPoints(), 4);
	EXPECT_EQ(a.getHealthPoints(), 4);
	EXPECT_EQ(a.getPhysicalDamage(), 3);
	EXPECT_EQ(a.getAttackCoolDown(), 2);
}

//attack tests
//attackdc test
TEST(Attacktest, attackcd) {
	Monster a = Monster("a", 10, 1, 0, 0, 1,"");
	Monster h = Monster("h", 10, 1, 0, 0, 10,"");
	Unit::attackcd(h, a);
	EXPECT_EQ(h.getHealthPoints(), 9);
	EXPECT_EQ(a.getHealthPoints(), 10);
}

//hero tests
//constructor
TEST(Hero, constructor) {
	Hero h = Hero("h", 4, 3, 0, 0, 2, "", 3, 2, 3, 0, 0, 0.2, 1, 1);
	EXPECT_EQ(h.getName(), "h");
	EXPECT_EQ(h.getMaxHealthPoints(), 4);
	EXPECT_EQ(h.getHealthPoints(), 4);
	EXPECT_EQ(h.getPhysicalDamage(), 3);
	EXPECT_EQ(h.getAttackCoolDown(), 2);
	EXPECT_EQ(h.getLevel(), 1);
	EXPECT_EQ(h.getExp(), 0);
	EXPECT_EQ(h.getLightRadius(), 1);
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
	Monster a = Monster("a", 13, 1, 0, 0, 4,"");
	Hero h = Hero("h", 10, 1, 0, 0, 2, "", 7, 2, 2, 2, 3, 0.3, 1, 1);
	h.fightTilDeath(a);
	EXPECT_EQ(h.getLevel(), 2);
	EXPECT_EQ(h.getMaxHealthPoints(), 12);
	EXPECT_EQ(h.getPhysicalDamage(), 3);
	EXPECT_EQ(h.getExp(), 6);
	EXPECT_EQ(h.getAttackCoolDown(), 2 * 0.3);
	EXPECT_EQ(h.getMagicalDamage(), 2);
	EXPECT_EQ(h.getDefense(), 3);
	EXPECT_EQ(h.getLightRadius(), 2);
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

	std::string expected =  "##############\n";
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
	EXPECT_EQ(test.getHeroPosition(), std::make_pair(2,1));
	std::list<std::pair<int,int>> m1,m2,m3;
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

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}


