#pragma once

#include <string>
#include <map>

class jsonparser
{

public:

    static std::map<std::string,std::string> jsonparse_f(std::string filename);

    static std::map<std::string,std::string> jsonparse_s(std::string json_in);

    static std::map<std::string,std::string> jsonparse_i(std::istream& stream);

};