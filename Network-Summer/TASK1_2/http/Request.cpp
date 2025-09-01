#include "Request.h"
#include <sstream>
#include <iostream>
#include <algorithm>

void Request::parse(const std::string &rawRequest)
{
    std::istringstream stream(rawRequest);
    std::string line;

    // Parse request line
    std::getline(stream, line);
    size_t methodEnd = line.find(' ');
    size_t pathEnd = line.find(' ', methodEnd + 1);

    method = line.substr(0, methodEnd);

    std::string fullPath = line.substr(methodEnd + 1, pathEnd - methodEnd - 1);

    // Split path + query
    size_t queryPos = fullPath.find('?');
    if (queryPos != std::string::npos)
    {
        path = fullPath.substr(0, queryPos);
        std::string queryString = fullPath.substr(queryPos + 1);

        // Parse query param
        std::istringstream qs(queryString);
        std::string pair;
        while (std::getline(qs, pair, '&'))
        {
            size_t eqPos = pair.find('=');
            if (eqPos != std::string::npos)
            {
                std::string key = pair.substr(0, eqPos);
                std::string value = pair.substr(eqPos + 1);
                params[key] = value;
            }
        }
    }
    else
    {
        path = fullPath;
    }

    // Parse headers
    while (std::getline(stream, line) && line != "\r")
    {
        size_t colonPos = line.find(':');
        if (colonPos != std::string::npos)
        {
            std::string key = line.substr(0, colonPos);
            std::string value = line.substr(colonPos + 1);

            // Trim spaces
            value.erase(value.begin(), std::find_if(value.begin(), value.end(), [](int ch)
                                                    { return !std::isspace(ch); }));
            value.erase(std::find_if(value.rbegin(), value.rend(), [](int ch)
                                     { return !std::isspace(ch); })
                            .base(),
                        value.end());

            headers[key] = value;
        }
    }

    // Read body
    std::ostringstream bodyStream;
    bodyStream << stream.rdbuf();
    body = bodyStream.str();
}

std::string Request::getMethod() const
{
    return method;
}

std::string Request::getPath() const
{
    return path;
}

std::string Request::getParam(const std::string &key) const
{
    auto it = params.find(key);
    if (it != params.end())
    {
        return it->second;
    }
    return "";
}

std::string Request::getHeader(const std::string &key) const
{
    auto it = headers.find(key);
    if (it != headers.end())
    {
        return it->second;
    }
    return "";
}

std::string Request::getBody() const
{
    return body;
}

std::map<std::string, std::string> Request::getBodyJSON() const
{
    return StringUtils::parseJSON(getBody());
}

std::string Request::getContentType() const
{
    size_t pos = path.rfind('.');
    if (pos == std::string::npos)
    {
        return "text/plain";
    }

    std::string ext = path.substr(pos + 1);
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

    if (ext == "html" || ext == "htm")
        return "text/html";
    if (ext == "css")
        return "text/css";
    if (ext == "js")
        return "application/javascript";
    if (ext == "json")
        return "application/json";
    if (ext == "map")
        return "application/json";
    if (ext == "png")
        return "image/png";
    if (ext == "jpg" || ext == "jpeg")
        return "image/jpeg";
    if (ext == "gif")
        return "image/gif";
    if (ext == "svg")
        return "image/svg+xml";
    if (ext == "pdf")
        return "application/pdf";
    if (ext == "txt")
        return "text/plain";
    if (ext == "ico")
        return "image/x-icon";

    return "application/octet-stream";
}
