#include "LoginController.h"
#include "core/SessionManager.h"

Response LoginController::handle(const Request &req)
{
    Response res;
    auto json = req.getBodyJSON();
    if (req.getMethod() == "POST")
    {
        std::string username = json["username"];
        std::string password = json["password"];
        std::string token = SessionManager::createSession(username);
        res.setStatus(200, "OK");
        res.setHeader("Set-Cookie", "token=" + token + "; Path=/; HttpOnly; Secure");
        res.setHeader("Content-Type", "text/plain");
        return res;
    }

    // else if (req.getMethod() == "GET")
    // {
    //     std::string cookie = req.getHeader("Cookie");
    //     std::cout << "[DEBUG] token:" << cookie << endl;  // token chưa được tách khỏi cookie
        

    //     if (SessionManager::isValid(token))
    //     {
    //         std::string username = SessionManager::getUsername(token);
    //         std::cout << "[DEBUG] username:" << username << endl;
    //         res.setStatus(200, "OK");
    //         res.setHeader("Content-Type", "application/json");
    //         res.setBody("{ \"username\": \"" + username + "\" }");
    //         return res;
    //     }
    //     else
    //     {
    //         res.sendUnauthorized();
    //     }
    // }

    return res;
}