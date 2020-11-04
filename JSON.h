#pragma once

#include <string>
#include <map>
#include <list>
#include <exception>
#include <iostream>
#include <type_traits>
#include <any>

class JSON
{

    //tárolási formátum: "[kulcs]:[érték]"
    std::list<std::string> json_list;
    
    //JSON szövegből olvas
    static std::list<std::string> jsonparse_s(std::string json_in);

    //JSON iterátorból olvas
    static std::list<std::string> jsonparse_i(std::istream& stream);

public:

    class ParseException :public std::exception
    {   };



    //JSON fájlt olvas
    static std::list<std::string> parseFromFile(std::string filename);


    //Megadott kulcs előfordulásának a számát adja meg
    int count(std::string key);

    //adott kulcshoz tatrtozó első változó értékét adja vissza
    template<typename T> 
    T get(std::string key)
    {
        std::any outval;
        for(auto const& iter : json_list)
        {
            
            if(iter.find(key) == 0)
            {
                std::string val = iter;
                val.erase(0,key.length()+2);

                
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
        }  
        return static_cast<T>(NULL);
    }



    JSON(const std::list<std::string>& in_list) :json_list(in_list) {}
};