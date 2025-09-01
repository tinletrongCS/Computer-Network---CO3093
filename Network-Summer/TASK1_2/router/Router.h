#pragma once
#include <map>
#include <functional>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "http/Request.h"
#include "http/Response.h"

class Router
{
public:
    using Handler = std::function<Response(const Request &)>;
    using Middleware = std::function<bool(const Request &, Response &)>;

    struct Route
    {
        Handler handler;
        Middleware middleware;
    };

    static void get(const std::string &path, Handler handler, Middleware middleware = nullptr)
    {
        routes()["GET:" + path] = {handler, middleware};
    }

    static void post(const std::string &path, Handler handler, Middleware middleware = nullptr)
    {
        routes()["POST:" + path] = {handler, middleware};
    }

    // Thêm DELETE
    static void remove(const std::string &path, Handler handler, Middleware middleware = nullptr)
    {
        routes()["DELETE:" + path] = {handler, middleware};
    }

    // Thêm UPDATE
    static void update(const std::string &path, Handler handler, Middleware middleware = nullptr)
    {
        routes()["PUT:" + path] = {handler, middleware};
    }

    static Response resolve(const Request &req)
    {
        std::string key = req.getMethod() + ":" + req.getPath();

        // Nếu là OPTIONS -> trả về luôn 204
        if (req.getMethod() == "OPTIONS")
        {
            Response res;
            res.setStatus(204, "No Content");
            return res;
        }

        auto it = routes().find(key);
        if (it != routes().end())
        {
            Route &route = it->second;

            Response res;
            if (route.middleware)
            {
                // Chạy middleware -> nếu false thì trả res luôn
                if (!route.middleware(req, res))
                {
                    return res;
                }
            }

            // Nếu middleware ok hoặc không có -> chạy handler
            return route.handler(req);
        }
        else
        {
            // Nếu không có route → thử trả file static
            Response staticRes;
            if (tryStaticFile(req, staticRes))
            {
                return staticRes;
            }

            // Nếu không có file -> trả 404
            Response res;
            res.sendError(404, "Not Found");
            return res;
        }
    }

private:
    static std::map<std::string, Route> &routes()
    {
        static std::map<std::string, Route> instance;
        return instance;
    }

    // Hàm check file static (trả về true nếu thành công)
    static bool tryStaticFile(const Request &req, Response &res)
    {
        std::string path = req.getPath();

        if (path == "/")
        {
            res.setStatus(200, "OK");
            res.setFileBody("./frontend/build/index.html", "text/html");
            return true;
        }

        std::string contentType = req.getContentType();

        if (contentType == "application/javascript" ||
            contentType == "text/css" ||
            contentType == "image/x-icon" ||
            contentType == "application/json" ||
            contentType.find("image/") == 0)
        {
            std::string filePath = "./frontend/build" + path;

            std::ifstream file(filePath, std::ios::binary);
            if (file)
            {
                res.setStatus(200, "OK");
                res.setFileBody(filePath, contentType);
                return true;
            }
        }

        return false;
    }
};
