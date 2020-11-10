#pragma once

#include <string>
#include <map>
#include <exception>
#include <iostream>
#include <type_traits>
#include <any>

class JSON
{

    //tárolási formátum: "[kulcs]:[érték]"
    std::map<std::string,std::string> json_list;

    //JSON iterátorból olvas
    static std::map<std::string,std::string> jsonparse_i(std::istream& stream);

public:

    class ParseException :public std::exception
    {   };



    //JSON fájlt olvas
    static std::map<std::string,std::string> parseFromFile(std::string filename);

    //JSON szövegből olvas
    static std::map<std::string,std::string> jsonparse_s(std::string json_in);



    //Megadott kulcs előfordulásának a számát adja meg
    int count(std::string key);

    //adott kulcshoz tatrtozó első változó értékét adja vissza
    template<typename T> 
    T get(std::string key)
    {
        std::any outval;
            
            if(json_list.count(key) > 0)
            {
                std::string val = json_list.find(key)->second;
                
                if (std::is_same<T, int>::value)
                {
                    outval = stoi(val);
                }
                else if  (std::is_same<T, double>::value)
                    {
                        outval = stod(val);
                    }
                    else
                    {
                        if  (std::is_same<T, std::string>::value)
                        {
                            outval = val;
                        } 
                    }    
                    
                return std::any_cast<T>(outval);
            }
            else
            {
                throw std::exception();
            }
            
        return static_cast<T>(NULL);
    }



    JSON(const std::map<std::string,std::string>& in_list) :json_list(in_list) {}
};