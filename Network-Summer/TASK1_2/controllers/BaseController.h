#pragma once
#include "http/Request.h"
#include "http/Response.h"

class BaseController
{
public:
    virtual ~BaseController() {}

    // Hàm base cho các controller kế thừa
    virtual Response handle(const Request &req)
    {
        Response res;
        res.setStatus(501, "Not Implemented");
        res.setBody("Base handle not implemented.");
        return res;
    }
};
