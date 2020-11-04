#include "jsonparser.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>


enum Processing { INIT, READKEY, SWITCH, READNUMVAL, READSTRVAL, END };

    std::map<std::string,std::string> jsonparser::jsonparse_i(std::istream& stream)
    {
        std::map<std::string,std::string> out;

        std::string input;
        char inchar;
        stream.get(inchar);
        if(inchar == '{')
        {
            Processing p = INIT;

            std::string key;

            //check if numeric value has a separator
            bool has_numdot = false;
            //check in SWITCH state if the ':' character is present
            bool has_switch = false;

            while(stream.get(inchar))
            {
                switch (p)
                {
                    //Initialise object reading
                case INIT:
                {
                    if (inchar == '"')
                        p = READKEY;
                    //ignore whitespace characters defined in JSON
                    else if (!isspace(inchar))
                    {
                        std::cerr << "[ERROR]: Failed to read key (expected \"), make sure the input streams formatting is correct!\n";
                        out.clear();
                        return out;
                    }
                    break;
                }

                //reading key
                case READKEY:
                {
                    //end of key
                    if (inchar == '"')
                    {
                        p = SWITCH;
                        key = input;
                        input.clear();
                    }
                    //part of key
                    else
                    {
                        input += inchar;

                    }
                    break;
                }

                //switching from reading key to reading value
                case SWITCH:
                {
                    switch (inchar)
                    {
                    case ':':
                        //dividing character found
                        if (!has_switch)
                        {
                            has_switch = true;
                            break;
                        }
                        //Error
                        else
                        {
                            std::cerr << "[ERROR]: Invalid starting character for value (expected \" or a number ), make sure the input streams formatting is correct!\n";
                            out.clear();
                            return out;
                        }
                        //beginning of string value
                    case '"':
                        if (has_switch)
                        {
                            p = READSTRVAL;
                            has_switch = false;
                        }
                        else
                        {
                            std::cerr << "[ERROR]: Invalid dividing character (expected : ), make sure the input streams formatting is correct!\n";
                            out.clear();
                            return out;
                        }
                        break;

                    default:
                        //check for numbers
                        if (inchar >= '0' && inchar <= '9')
                        {
                            if (has_switch)
                            {
                                has_numdot = false;
                                p = READNUMVAL;
                                input += inchar;
                                has_switch = false;
                            }
                            else
                            {
                                std::cerr << "[ERROR]: Invalid dividing character (expected : ), make sure the input streams formatting is correct!\n";
                                out.clear();
                                return out;
                            }
                        }
                        else
                        {
                            //Check for whitespace
                            if (!isspace(inchar))
                            {
                                std::cerr << "[ERROR]: Invalid dividing character (expected : ), make sure the input streams formatting is correct!\n";
                                out.clear();
                                return out;
                            }
                            break;
                        }
                    }
                    break;
                }

                //reading string value
                case READSTRVAL:
                {
                    //end of value
                    if (inchar == '"')
                    {

                        p = END;
                        out.insert({ key,input });
                        key.clear();
                        input.clear();
                    }
                    //part of value
                    else
                    {
                        input += inchar;
                    }
                    break;
                }

                //reading numeric value
                case READNUMVAL:
                {
                    //Check for number
                    if (inchar >= '0' && inchar <= '9')
                    {
                        input += inchar;
                    }
                    else
                    {
                        //Check for separator
                        if (inchar == '.')
                        {
                            if (has_numdot)
                            {
                                std::cerr << "[ERROR]: Number already has separator, make sure the input streams formatting is correct!\n";
                                out.clear();
                                return out;
                            }
                            else
                            {
                                input += inchar;
                                has_numdot = true;
                            }
                        }
                        else
                        {
                            //Check for end of value
                            if (isspace(inchar) || inchar == '}')
                            {
                                if (input.back() == '.')
                                {
                                    input.pop_back();
                                }
                                else {}
                                out.insert({ key,input });
                                key.clear();
                                input.clear();
                                p = END;
                            }
                            else
                            {
                                if (inchar == ',')
                                {
                                    out.insert({ key,input });
                                    key.clear();
                                    input.clear();
                                    p = INIT;
                                }
                                else
                                {
                                    std::cerr << "[ERROR]: Invalid input character (expected number) make sure the input streams formatting is correct!\n";
                                    out.clear();
                                    return out;
                                }
                            }
                        }
                    }
                    break;
                }

                //end of object reading
                case END:
                {
                    switch (inchar)
                    {
                        //read next object
                    case ',':
                        p = INIT;
                        break;
                        //end of parse
                    case '}':
                        return out;
                        //error
                    default:
                        if (!isspace(inchar))
                        {
                            std::cerr << "[ERROR]: Invalid ending character (expected , or } ), make sure the input streams formatting is correct!\n";
                            out.clear();
                            return out;
                        }
                        break;
                    }
                    break;
                }
                }
            }
        }
        else
        {
            std::cerr << "[ERROR]: Input streams content is not recognised as JSON!\n";
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

