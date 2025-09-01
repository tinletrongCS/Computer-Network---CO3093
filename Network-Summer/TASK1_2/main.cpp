#include "server/TCPServer.h"
#include <iostream>
#include <cstdlib>

int main(int argc, char *argv[])
{
    int port = 8080;
    if (argc > 1)
    {
        port = std::atoi(argv[1]);
        if (port <= 0 || port > 65535)
        {
            port = 8080;
        }
    }

    TCPServer server(port);
    server.run();

    return 0;
}