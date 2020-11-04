#pragma once

#include <string>
#include <map>
#include <list>
#include <exception>
#include <iostream>
#include <type_traits>

class JSON
{

    //tárolási formátum: "[kulcs]:[érték]"
    std::list<std::string> json_list;

public:

    class ParseException :public std::exception
    {   };



    //JSON fájlt olvas
    static std::list<std::string> parseFromFile(std::string filename);

    //JSON szövegből olvas
    static std::list<std::string> jsonparse_s(std::string json_in);

    //JSON iterátorból olvas
    static std::list<std::string> jsonparse_i(std::istream& stream);

    //Megadott kulcs előfordulásának a számát adja meg
    int count(std::string key);

    //adott kulcshoz tatrtozó első változó értékét adja vissza
    template<typename T> 
    T get(std::string key)
    {
            T outval;
        for(auto const& iter : json_list)
        {
            if(iter.find(key) == 0)
            {
                std::string value = iter;
                value.erase(0,key.length()+2);
                if constexpr (std::is_integral_v<T>)
                {
                    outval = stoi(value);
                }
                else if constexpr (std::is_floating_point_v<T>)
                    {
                        outval = stod(value);
                    }
                    else
                    {
                        if constexpr (std::is_class_v<std::string>)
                        {
                            outval = value;
                        }
                        
                    }    
                    
                return outval;
            }
        }  
        return static_cast<T>(NULL);
    }



    JSON(std::list<std::string> in_list) :json_list(in_list) {}
};