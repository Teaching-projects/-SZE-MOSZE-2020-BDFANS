#include "jsonparser.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

    std::map<std::string,std::string> jsonparser::jsonparse_i(std::istream& stream)
    {
        std::map<std::string,std::string> out;

        std::string input;
        stream >> input;
        if(input == "{")
        {
            std::string key;
            bool has_key = false;
            while(stream >> input && input != "}")
            {
                if(input != ":")
                {
                    //value
                    if(has_key)
                    {
                        //last value
                        if(input[input.length() - 1] == ',')
                        {
                            input = input.substr(0, input.size()-1);
                        }
                        input.erase(std::remove(input.begin(), input.end(), '"'), input.end());
                        out.insert({ key, input });
                        has_key = false;
                    }
                    //key
                    else
                    {
                        input.erase(std::remove(input.begin(), input.end(), '"'), input.end());
                        key = input;
                    }
                }
                //":"
                else
                {
                    has_key = true;
                }
            }
        }
        else
        {
            std::cerr << "[ERROR]: Files content is not recognised as JSON!\n";
        }
        
        return out;
    }


    std::map<std::string,std::string> jsonparser::jsonparse_f(std::string filename)
    {
        try
        {
            std::ifstream ifile;
            ifile.open(filename);

            std::map<std::string,std::string> out = jsonparser::jsonparse_i(ifile);

            ifile.close();

            return out;
        }
        catch(const std::exception& e)
        {
            std::cerr << "[ERROR]: jsonparser failed to read file! Make sure the file provided is valid!" << std::endl;
            throw  std::exception();
        } 
    }

    std::map<std::string,std::string> jsonparser::jsonparse_s(std::string json_in)
    {
        
        std::stringstream sstream(json_in);

        return jsonparser::jsonparse_i(sstream);
    }

