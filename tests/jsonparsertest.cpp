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
	ASSERT_EQ(jsonparser::jsonparse_f("parsertestfiles/jsonparsertest.txt"), comp);
}

TEST(Fileparser, no_whitespaces) {
	std::map<std::string, std::string> comp = make_compmap();
	ASSERT_EQ(jsonparser::jsonparse_f("parsertestfiles/nowhitespace.txt"), comp);
}

TEST(Fileparser, many_whitespaces) {
	std::map<std::string, std::string> comp = make_compmap();
	ASSERT_EQ(jsonparser::jsonparse_f("parsertestfiles/manywhitespace.txt"), comp);
}

TEST(Fileparser, invalid_file) {
	std::map<std::string, std::string> empty;

	const char* expected = "[ERROR]: Input streams content is not recognised as JSON!\n";

	testing::internal::CaptureStderr();

	ASSERT_EQ(jsonparser::jsonparse_f("parsertestfiles/invalidfile.txt"), empty);

	std::string output = testing::internal::GetCapturedStderr();

	ASSERT_STREQ(expected, output.c_str());
}

TEST(Stringparser, stringparse) {
	std::string instring = "{	\"str1\" : \"test\", \"int1\" : 2, \"int2\" : 3.3, \"str2\" : \"tset\" }";
	std::map<std::string, std::string> comp = make_compmap();
	ASSERT_EQ(jsonparser::jsonparse_s(instring), comp);
}

TEST(Parsingerror, broken_key) {
	std::map<std::string, std::string> empty;

	const char* expected = "[ERROR]: Failed to read key (expected \"), make sure the input streams formatting is correct!\n";
	std::string instring = "{	3 \"str1\" : \"test\", \"int1\" : 2, \"int2\" : 3, \"str2\" : \"tset\" }";

	testing::internal::CaptureStderr();

	ASSERT_EQ(jsonparser::jsonparse_s(instring), empty);

	std::string output = testing::internal::GetCapturedStderr();

	ASSERT_STREQ(expected, output.c_str());
}

TEST(Parsingerror, broken_separator) {
	std::map<std::string, std::string> empty;

	const char* expected = "[ERROR]: Invalid dividing character (expected : ), make sure the input streams formatting is correct!\n";
	std::string instring = "{	\"str1\" : \"test\", \"int1\" % 2, \"int2\" : 3, \"str2\" : \"tset\" }";

	testing::internal::CaptureStderr();
	ASSERT_EQ(jsonparser::jsonparse_s(instring), empty);
	std::string output = testing::internal::GetCapturedStderr();
	ASSERT_STREQ(expected, output.c_str());
}

TEST(Parsingerror, broken_numvalue) {
	std::map<std::string, std::string> empty;
	const char* expected = "[ERROR]: Invalid input character (expected number) make sure the input streams formatting is correct!\n";
	std::string instring = "{	\"str1\" : \"test\", \"int1\" : 2two, \"int2\" : 3, \"str2\" : \"tset\" }";
	testing::internal::CaptureStderr();
	ASSERT_EQ(jsonparser::jsonparse_s(instring), empty);
	std::string output = testing::internal::GetCapturedStderr();
	ASSERT_STREQ(expected, output.c_str());
}

TEST(Parsingerror, broken_numvalue_separators) {
	std::map<std::string, std::string> empty;
	const char* expected = "[ERROR]: Number already has separator, make sure the input streams formatting is correct!\n";
	std::string instring = "{	\"str1\" : \"test\", \"int1\" : 2, \"int2\" : 3.3.3, \"str2\" : \"tset\" }";
	testing::internal::CaptureStderr();
	ASSERT_EQ(jsonparser::jsonparse_s(instring), empty);
	std::string output = testing::internal::GetCapturedStderr();
	ASSERT_STREQ(expected, output.c_str());
}


int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}


