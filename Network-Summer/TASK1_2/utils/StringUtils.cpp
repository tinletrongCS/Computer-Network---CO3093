#include "StringUtils.h"

std::string StringUtils::trim(const std::string &s)
{
    size_t start = s.find_first_not_of(" \t\n\r\"");
    size_t end = s.find_last_not_of(" \t\n\r\"");
    return (start == std::string::npos) ? "" : s.substr(start, end - start + 1);
}

std::vector<std::string> StringUtils::split(const std::string &s, char delimiter)
{
    std::vector<std::string> tokens;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delimiter))
    {
        tokens.push_back(item);
    }
    return tokens;
}

std::map<std::string, std::string> StringUtils::parseJSON(const std::string &json)
{
    std::map<std::string, std::string> result;

    if (json.empty() || json.front() != '{' || json.back() != '}')
        throw std::invalid_argument("Invalid JSON format");

    std::string inner = json.substr(1, json.size() - 2);
    std::istringstream ss(inner);
    std::string pair;

    while (std::getline(ss, pair, ','))
    {
        size_t colon = pair.find(':');
        if (colon == std::string::npos)
            continue;

        std::string key = pair.substr(0, colon);
        std::string value = pair.substr(colon + 1);

        key = StringUtils::trim(key);
        value = StringUtils::trim(value);

        result[key] = value;
    }

    return result;
}
