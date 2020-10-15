#include "../jsonparser.h"
#include <gtest/gtest.h>
#include <iostream>
#include <map>

TEST(Fileparser, fileparse) {
	std::map<std::string, std::string> comp;
	comp.insert({ "str1", "test" });
	comp.insert({ "int1", "2" });
	comp.insert({ "int2", "3" });
	comp.insert({ "str2", "tset" });
	ASSERT_EQ(jsonparser::jsonparse_f("parsertestfiles/jsonparsertest.txt"), comp);
}

TEST(Fileparser, invalid_file) {
	std::map<std::string, std::string> empty;

	const char* expected = "[ERROR]: Files content is not recognised as JSON!\n";

	testing::internal::CaptureStderr();

	ASSERT_EQ(jsonparser::jsonparse_f("parsertestfiles/invalidfile.txt"), empty);

	std::string output = testing::internal::GetCapturedStderr();

	ASSERT_STREQ(expected, output.c_str());
}

TEST(Stringparser, stringparse) {
	std::string instring = "{	\"str1\" : \"test\", \"int1\" : 2, \"int2\" : 3, \"str2\" : \"tset\" }";
	std::map<std::string, std::string> comp;
	comp.insert({ "str1", "test" });
	comp.insert({ "int1", "2" });
	comp.insert({ "int2", "3" });
	comp.insert({ "str2", "tset" });
	ASSERT_EQ(jsonparser::jsonparse_s(instring), comp);
}


int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}


