#pragma once

#include <string>
#include <map>
#include <fstream>

class Response
{
    int statusCode = 200;
    std::string statusText = "OK";
    std::map<std::string, std::string> headers;
    std::string body;

public:
    Response() = default;

    void setStatus(int code, const std::string &text);
    void setHeader(const std::string &key, const std::string &value);
    void setBody(const std::string &bodyContent);
    void setFileBody(const std::string &filePath, const std::string &contentType = "application/octet-stream");

    // Common response patterns
    void sendUnauthorized();
    void sendError(int code, const std::string &message);

    std::string toString();
};