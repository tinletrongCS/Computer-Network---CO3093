#pragma once
#include "BaseController.h"
#include "models/LoginModel.h"

class LoginController : public BaseController
{
public:
    Response handle(const Request &req) override;
};
