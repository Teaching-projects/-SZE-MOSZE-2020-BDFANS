#include "JSON.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>


enum Processing { INIT, READKEY, SWITCH, READNUMVAL, READSTRVAL, END };

    std::list<std::string> JSON::jsonparse_i(std::istream& stream)
    {
        std::list<std::string> out;

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
                        throw  ParseException();
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
                        else
                        {
                            throw  ParseException();
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
                            throw  ParseException();
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
                                throw  ParseException();
                            }
                        }
                        else
                        {
                            //Check for whitespace
                            if (!isspace(inchar))
                            {
                                throw  ParseException();
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
                        out.push_back(key+": "+input);
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
                                throw  ParseException();
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
                                out.push_back(key+": "+input);
                                key.clear();
                                input.clear();
                                p = END;
                            }
                            else
                            {
                                if (inchar == ',')
                                {
                                    out.push_back(key+": "+input);
                                    key.clear();
                                    input.clear();
                                    p = INIT;
                                }
                                else
                                {
                                    throw  ParseException();
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
                            throw  ParseException();
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
            throw  ParseException();
        }
        
        return out;
    }


    std::list<std::string> JSON::parseFromFile(std::string filename)
    {
        try
        {
            std::ifstream ifile;
            ifile.open(filename);
            std::list<std::string> out = JSON::jsonparse_i(ifile);
            ifile.close();

            return out;
        }
        catch(const ParseException& e)
        {
            throw  ParseException();
        } 
    }

    std::list<std::string> JSON::jsonparse_s(std::string json_in)
    {
        
        std::stringstream sstream(json_in);

        return JSON::jsonparse_i(sstream);
    }

    int JSON::count(std::string key)
    {
        int keycount = 0;

        for(auto const& iter : json_list)
        {
            if(iter.find(key))
            {
                keycount++;
            }
        }  
        return keycount;
    }
