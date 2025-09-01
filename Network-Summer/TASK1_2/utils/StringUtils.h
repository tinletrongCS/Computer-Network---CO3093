#pragma once
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <iostream>

using namespace std;

class StringUtils
{
public:
    static std::string trim(const std::string &s);
    static std::vector<std::string> split(const std::string &s, char delimiter);
    static std::map<std::string, std::string> parseJSON(const std::string &body);
};
