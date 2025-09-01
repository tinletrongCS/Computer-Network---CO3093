#pragma once
#include "BaseModel.h"

class LoginModel : public BaseModel
{
public:
    bool authenticate(const std::string &username, const std::string &password)
    {
        return username == "admin" && password == "1234";
    }
};
