#pragma once
#include "BaseController.h"
#include "models/ProductModel.h"

class ProductController : public BaseController
{
private:
    ProductModel model;

public:
    Response handle(const Request &req) override;

    Response storeProduct(const Request &req);
    Response listProducts(const Request &req);
    Response removeProductById(const Request &req);
    Response updateProduct(const Request &req);
};
