#include "TCPServer.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>

using namespace std;

void TCPServer::run()
{
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);
    bind(server_fd, (sockaddr *)&addr, sizeof(addr));
    listen(server_fd, 5);

    std::cout << "[Server] Listening on port " << port << "...\n";

    while (true)
    {
        int clientSocket = accept(server_fd, nullptr, nullptr);
        if (clientSocket < 0)
        {
            std::cerr << "[Server] Failed to accept connection\n";
            continue;
        }

        char buffer[2048] = {0};
        int len = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (len <= 0)
        {
            close(clientSocket);
            continue;
        }
        std::string input(buffer, len);

        //! ---------------------------------------------------------
        std::cout << input << std::endl;

        Request req;
        req.parse(input);

        Response res = Router::resolve(req);
        res.setHeader("Access-Control-Allow-Origin", req.getHeader("Origin"));
        res.setHeader("Access-Control-Max-Age", "600");
        res.setHeader("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        res.setHeader("Access-Control-Allow-Headers", "Content-Type, Authorization");
        res.setHeader("Access-Control-Allow-Credentials", "true");

        std::string response = res.toString();
        send(clientSocket, response.c_str(), response.size(), 0);
        // cout << response << endl;
        //!----------------------------------
        send(clientSocket, response.c_str(), response.size(), 0);
        close(clientSocket);
    }

    close(server_fd);
}
