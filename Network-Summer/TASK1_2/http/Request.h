#pragma once

#include <string>
#include <map>
#include <algorithm>

#include "utils/StringUtils.h"
class Request
{
private:
    std::string method;
    std::string path;
    std::map<std::string, std::string> params; // query param
    std::map<std::string, std::string> headers;
    std::string body;

public:
    Request() = default;

    void parse(const std::string &rawRequest);

    std::string getMethod() const;
    std::string getPath() const;
    std::string getParam(const std::string &key) const;
    std::string getHeader(const std::string &key) const;
    std::string getBody() const;
    std::map<std::string, std::string> getBodyJSON() const;

    std::string getContentType() const;
};
