#pragma once
#include "http/Request.h"
#include "http/Response.h"
#include "router/Router.h"
#include "routes.h"
class TCPServer
{
    int port;

public:
    TCPServer(int p) : port(p)
    {
        setupRoutes();
    }
    void run();
};