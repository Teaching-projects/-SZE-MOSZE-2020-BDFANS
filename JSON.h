/**
 * @file JSON.h
 * @class JSON
 *
 * @author BDFANS
 *
 * @brief header for JSON class
 * @version 0.4.0
 *
 *
 * @date 2020-11-13
 *
 */
#pragma once

#include <string>
#include <map>
#include <exception>
#include <iostream>
#include <type_traits>
#include <any>

class JSON
{

    ///tárolási formátum: "[key]:[value]"
    std::map<std::string,std::string> json_list;

    ///Reading from JSON iterator
    static std::map<std::string,std::string> jsonparse_i(std::istream& stream);

public:

    class ParseException :public std::exception
    {   };



    ///Reading from JSON file
    static std::map<std::string,std::string> parseFromFile(std::string filename);

    ///Reading from JSON text
    static std::map<std::string,std::string> jsonparse_s(std::string json_in);



    ///Gives back the number of occurrences of the specified key
    int count(std::string key);

    ///returns the value of the first variable associated with a given key
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