#include "Response.h"
#include <sstream>
#include <iostream>

void Response::setStatus(int code, const std::string &text)
{
    statusCode = code;
    statusText = text;
}

void Response::setHeader(const std::string &key, const std::string &value)
{
    headers[key] = value;
}

void Response::setBody(const std::string &bodyContent)
{
    body = bodyContent;
}

void Response::setFileBody(const std::string &filePath, const std::string &contentType)
{
    std::cout << filePath << std::endl;
    std::ifstream file(filePath, std::ios::in | std::ios::binary);
    if (!file.is_open())
    {
        sendError(404, "Not Found");
        return;
    }

    std::stringstream ss;
    ss << file.rdbuf();
    file.close();

    body = ss.str();
    setHeader("Content-Type", contentType);
    setBody(body);
}

void Response::sendUnauthorized()
{
    setStatus(401, "Unauthorized");
    setBody("401 Unauthorized");
    setHeader("Content-Type", "text/plain");
}

void Response::sendError(int code, const std::string &message)
{
    setStatus(code, message);
    setBody(std::to_string(code) + " " + message);
    setHeader("Content-Type", "text/plain");
}

std::string Response::toString()
{
    std::ostringstream response;
    response << "HTTP/1.1 " << statusCode << " " << statusText << "\r\n";

    if (headers.find("Content-Length") == headers.end())
    {
        response << "Content-Length: " << body.size() << "\r\n";
    }

    for (const auto &h : headers)
    {
        response << h.first << ": " << h.second << "\r\n";
    }

    response << "\r\n";
    response << body;

    return response.str();
}
