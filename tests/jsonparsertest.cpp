#include "../JSON.h"
#include "../Hero.h"
#include "../Monster.h"
#include <gtest/gtest.h>
#include <iostream>
#include <map>


std::map<std::string, std::string> make_compmap()
{
	std::map<std::string, std::string> comp;
	comp.insert({ "str1", "test" });
	comp.insert({ "int1", "2" });
	comp.insert({ "int2", "3.3" });
	comp.insert({ "str2", "tset" });

	return comp;
}
//fileparser tests
//normal fileparse test
TEST(Fileparser, fileparse) {
	std::map<std::string, std::string> comp = make_compmap();
	ASSERT_EQ(JSON::parseFromFile("parsertestfiles/jsonparsertest.txt"), comp);
}

//file with no whitespaces
TEST(Fileparser, no_whitespaces) {
	std::map<std::string, std::string> comp = make_compmap();
	ASSERT_EQ(JSON::parseFromFile("parsertestfiles/nowhitespace.txt"), comp);
}

//file with many whitespaces
TEST(Fileparser, many_whitespaces) {
	std::map<std::string, std::string> comp = make_compmap();
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
	std::map<std::string, std::string> comp = make_compmap();
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

//Monster tests
//constructor
TEST(Monster, constructor) {
	Damage dmg(3, 1);
	Monster a = Monster("a", 4, dmg, 1, 2);
	EXPECT_EQ(a.getName(), "a");
	EXPECT_EQ(a.getMaxHealthPoints(), 4);
	EXPECT_EQ(a.getHealthPoints(), 4);
	EXPECT_EQ(a.getDamage(), dmg);
	EXPECT_EQ(a.getDefense(), 1);
	EXPECT_EQ(a.getAttackCoolDown(), 2);
}

//attack tests
//attackdc test
TEST(Attacktest, attackcd) {
	Damage dmg(1, 1);
	Monster a = Monster("a", 10, dmg, 1, 1);
	Monster h = Monster("h", 10, dmg, 1, 10);
	Unit::attackcd(h,a);
	EXPECT_EQ(h.getHealthPoints(), 9);
	EXPECT_EQ(a.getHealthPoints(), 10);
}


//hero tests
//constructor
TEST(Hero, constructor) {
	Damage dmg(3, 2);
	Hero h = Hero("h", 4, dmg, 1 ,2,3,2,3,0.2);
	EXPECT_EQ(h.getName(), "h");
	EXPECT_EQ(h.getMaxHealthPoints(), 4);
	EXPECT_EQ(h.getHealthPoints(), 4);
	EXPECT_EQ(h.getDamage(), dmg);
	EXPECT_EQ(h.getDefense(), 1);
	EXPECT_EQ(h.getAttackCoolDown(), 2);
	EXPECT_EQ(h.getLevel(), 1);
	EXPECT_EQ(h.getExp(), 0);
}

//XP gain test
TEST(Hero, xpGain) {
	Damage mdmg(1,0);
	Damage hdmg(5, 2);
	Monster a = Monster("a", 3, mdmg, 1, 1);
	Hero h = Hero("h", 10, hdmg, 2, 1, 100);
	h.attack(a);
	EXPECT_EQ(h.getExp(), 3);
}

//fighttildeath test
TEST(Hero, fightildeath) {
	Damage mdmg(1, 1);
	Damage hdmg(2, 1);
	Monster a = Monster("a", 10, mdmg, 1,1);
	Hero h = Hero("h", 10, hdmg, 1, 1, 100);
	h.fightTilDeath(a);
	EXPECT_EQ(h.isAlive(), true);
	EXPECT_EQ(a.isAlive(), false);
}

//lvlup test
TEST(Hero, lvlup) {
	Damage mdmg(1, 1);
	Damage hdmg(1, 1);
	Monster a = Monster("a", 13, mdmg, 1, 4);
	Hero h = Hero("h", 10, hdmg, 1,2, 7,2,1,1,1,0.3);
	h.fightTilDeath(a);
	EXPECT_EQ(h.getLevel(), 2);
	EXPECT_EQ(h.getMaxHealthPoints(), 12);
	EXPECT_EQ(h.getPhysicalDamage(), 2);
	EXPECT_EQ(h.getMagicalDamage(), 2);
	EXPECT_EQ(h.getDefense(), 2);
	EXPECT_EQ(h.getExp(), 6);
	EXPECT_EQ(h.getAttackCoolDown(), 2*0.3);
}



int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}


