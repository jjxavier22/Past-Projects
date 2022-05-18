//
// Created by Jiss Xavier on 2019-04-24.
//
#include <iostream>
#include <string>
#include <algorithm>
#include "gameSimulation.h"

//trims all the white space before the word/input
std::string ltrim(std::string& s)
{
    size_t start = s.find_first_not_of(" \n\r\t\f\v");
    return (start == std::string::npos) ? "" : s.substr(start);
}

//trims all the white space after the word/input
std::string rtrim(std::string& s)
{
    size_t end = s.find_last_not_of(" \n\r\t\f\v");
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}
