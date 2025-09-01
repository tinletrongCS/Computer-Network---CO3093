#pragma once
#include "SessionManager.h"
#include "http/Request.h"
#include "http/Response.h"

class AuthMiddleware
{
public:
    static bool handle(const Request &req, Response &res)
    {
        std::string token;

        // Check Authorization header first
        std::string authHeader = req.getHeader("Authorization");
        if (!authHeader.empty() && authHeader.find("Bearer ") == 0)
        {
            std::cout << "[DEBUG] Check 'bearer' header " << endl;
            token = parseTokenFromAuthorization(authHeader);
        }
        else
        {
            // Fallback to Cookie header
            std::cout << "[DEBUG] Check 'cookie' header " << endl;
            std::string cookie = req.getHeader("Cookie");
            std::cout << "[DEBUG] Cookie got from header: " << cookie << endl;
            token = parseTokenFromCookie(cookie);
            std::cout << "[DEBUG] Token after parsed: " << token << endl;
        }

        if (SessionManager::isValid(token))
        {
            std::cout << "[DEBUG] Valid token " << endl;
            return true;
        }

        res.setStatus(401, "Unauthorized");
        res.setBody("Invalid or missing session.");
        std::cout << "[DEBUG] AuthMiddleware.h" << endl;
        return false;
    }

private:
    static std::string parseTokenFromAuthorization(const std::string &authHeader)
    {
        const std::string prefix = "Bearer ";
        return authHeader.substr(prefix.length());
    }

    static std::string parseTokenFromCookie(const std::string &cookie)
    {
        const std::string prefix = "token=";
        size_t pos = cookie.find(prefix);
        if (pos == std::string::npos)
            return "";

        size_t start = pos + prefix.length();
        size_t end = cookie.find(';', start);
        if (end == std::string::npos)
            end = cookie.length();

        return cookie.substr(start, end - start);
    }
};
