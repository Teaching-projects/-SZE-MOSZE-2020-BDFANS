#include "../JSON.h"
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

TEST(Fileparser, fileparse) {
	std::map<std::string, std::string> comp = make_compmap();
	ASSERT_EQ(JSON::parseFromFile("parsertestfiles/jsonparsertest.txt"), comp);
}

TEST(Fileparser, no_whitespaces) {
	std::map<std::string, std::string> comp = make_compmap();
	ASSERT_EQ(JSON::parseFromFile("parsertestfiles/nowhitespace.txt"), comp);
}

TEST(Fileparser, many_whitespaces) {
	std::map<std::string, std::string> comp = make_compmap();
	ASSERT_EQ(JSON::parseFromFile("parsertestfiles/manywhitespace.txt"), comp);
}

TEST(Fileparser, invalid_file) {
	ASSERT_THROW(JSON::parseFromFile("parsertestfiles/invalidfile.txt"),JSON::ParseException);
}

TEST(Stringparser, stringparse) {
	std::string instring = "{	\"str1\" : \"test\", \"int1\" : 2, \"int2\" : 3.3, \"str2\" : \"tset\" }";
	std::map<std::string, std::string> comp = make_compmap();
	ASSERT_EQ(JSON::jsonparse_s(instring), comp);
}

TEST(Parsingerror, broken_key) {
	std::string instring = "{	3 \"str1\" : \"test\", \"int1\" : 2, \"int2\" : 3, \"str2\" : \"tset\" }";

	ASSERT_THROW(JSON::jsonparse_s(instring), JSON::ParseException);

}

TEST(Parsingerror, broken_separator) {
	std::string instring = "{	\"str1\" : \"test\", \"int1\" % 2, \"int2\" : 3, \"str2\" : \"tset\" }";

	ASSERT_THROW(JSON::jsonparse_s(instring), JSON::ParseException);

}

TEST(Parsingerror, broken_numvalue) {
	std::string instring = "{	\"str1\" : \"test\", \"int1\" : 2two, \"int2\" : 3, \"str2\" : \"tset\" }";
	
	ASSERT_THROW(JSON::jsonparse_s(instring), JSON::ParseException);
}

TEST(Parsingerror, broken_numvalue_separators) {
	std::string instring = "{	\"str1\" : \"test\", \"int1\" : 2, \"int2\" : 3.3.3, \"str2\" : \"tset\" }";

	ASSERT_THROW(JSON::jsonparse_s(instring), JSON::ParseException);
}


int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}


