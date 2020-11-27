/**
 * @file JSON.h
 * @class JSON
 *
 * @author BDFANS
 *
 * @brief header for JSON class
 * @version 0.5.0
 *
 *
 * @date 2020-11-27
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
    /**Stores the  processed JSON data in a map
    *Storage format: "[key]:[value]"
    */
    std::map<std::string,std::string> json_list;

    /**
    * @brief this function parses JSON data from an inputstream
    *
    * @param stream the name of the input stream
    *
    * @throw ParseException this function throws an exception if the parsing fails
    */
    static std::map<std::string,std::string> jsonparse_i(std::istream& stream);

public:
    ///This is the exception thrown when the JSON parsing fails
    class ParseException :public std::exception
    {   };

    /**
    * @brief this function parses JSON data from a file
    *
    * @param filename the name of the input file
    *
    * @throw ParseException this function throws an exception if the parsing fails  
    */
    static std::map<std::string,std::string> parseFromFile(std::string filename);

    /**
    * @brief this function parses JSON data from a text
    *
    * @param json_in the name of the input text
    *
    * @throw ParseException this function throws an exception if the parsing fails
    */
    static std::map<std::string,std::string> jsonparse_s(std::string json_in);



    /**
    * @brief Gives back the number of occurrences of the specified key
    *
    * @param key the object key being counted
    */
    int count(std::string key);

    /**
    * @brief Returns the value of the first variable associated with a given key
    *
    * @param key the object key the function searches for
    *
    * The output typename(T) can be int, double, or string
    *
    * @throw Exception this function throws an exception if the function can't find the key, or can't process the output type
    */   

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


    /**
    * @brief Construct a new JSON object
    *
    * @param in_list the input map containing processed JSON data
    */
    JSON(const std::map<std::string,std::string>& in_list) :json_list(in_list) {}
};