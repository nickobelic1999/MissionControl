//
// Created by nickobelic1999 on 7/24/22.
//

#include <algorithm>
#include "utils.hpp"


using namespace MissionControl_Utils;

std::string Utils::ToLower(std::string str)
{
    std::string s = str;
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

Utils::Utils()
{}

Utils::~Utils()
{}