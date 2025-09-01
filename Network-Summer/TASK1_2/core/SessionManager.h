#pragma once
#include <string>
#include <map>
#include <iostream>
#include "utils/TokenGenerator.h"

class SessionManager
{
public:
    static std::string createSession(const std::string &username)
    {
        std::string token = TokenGenerator::generate();
        sessions[token] = username;
        std::cout << username << " " << token << std::endl;
        return token;
    }

    static bool isValid(const std::string &token)
    {
        return sessions.find(token) != sessions.end();
    }

    static std::string getUsername(const std::string &token)
    {
        auto it = sessions.find(token);
        if (it != sessions.end())
            return it->second;
        return "";
    }

private:
    static std::map<std::string, std::string> sessions;
};
