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
#include <variant>
#include <list>


#define JSONDATA std::variant<std::string,int,double,JSON::list>

class JSON
{

public:

    ///Definition of multiple data containing list
    typedef std::list<std::variant<std::string,int,double>> list;

private:
    /**Stores the  processed JSON data in a map
    *Storage format: "[key]:[value]"
    */
    std::map<std::string,JSONDATA> json_list;

    /**
    * @brief this function parses JSON data from an inputstream
    *
    * @param stream the name of the input stream
    *
    * @throw ParseException this function throws an exception if the parsing fails
    */
    static std::map<std::string,JSONDATA> jsonparse_i(std::istream& stream);

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
    static std::map<std::string,JSONDATA> parseFromFile(std::string filename);

    /**
    * @brief this function parses JSON data from a text
    *
    * @param json_in the name of the input text
    *
    * @throw ParseException this function throws an exception if the parsing fails
    */
    static std::map<std::string,JSONDATA> jsonparse_s(std::string json_in);



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

                {
                    JSONDATA val = json_list.find(key)->second;
                    if (std::is_same<T, JSON::list>::value)
                    {
                        outval = std::get<JSON::list>(val);
                    }
                    else if (std::is_same<T, int>::value)
                    {
                        outval = std::get<int>(val);
                    }
                    else if  (std::is_same<T, double>::value)
                        {
                            outval = std::get<double>(val); 
                        }
                        else{
                        if  (std::is_same<T, std::string>::value)
                        {
                            outval = std::get<std::string>(val);
                        } 
                    } 
                }    
                return std::any_cast<T>(outval);
            }
            else
            {
                throw std::exception();
            }
    }


    /**
    * @brief Construct a new JSON object
    *
    * @param in_list the input map containing processed JSON data
    */
    JSON(const std::map<std::string,JSONDATA>& in_list) :json_list(in_list) {}
};