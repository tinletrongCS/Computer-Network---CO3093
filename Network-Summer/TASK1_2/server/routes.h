#pragma once
#include "router/Router.h"
#include "controllers/LoginController.h"
#include "controllers/ProductController.h"
#include "core/AuthMiddleware.h"

inline void setupRoutes()
{
    Router::post("/login", [](const Request &req)
                 {
        LoginController controller;
        return controller.handle(req); });

    Router::get("/product", [](const Request &req)
                {
        ProductController controller;
        return controller.listProducts(req); }, AuthMiddleware::handle);

    Router::post("/product", [](const Request &req)
                 {
        ProductController controller;
        return controller.storeProduct(req); }, AuthMiddleware::handle);

    Router::remove("/product", [](const Request &req)
                   {
        ProductController controller;
        return controller.removeProductById(req); }, AuthMiddleware::handle);

    Router::update("/product", [](const Request &req) 
                    {
        ProductController controller;
        return controller.updateProduct(req); }, AuthMiddleware::handle); 

    Router::get("/swagger.yaml", [](const Request &req)
                   {
    Response res;
    res.setFileBody("./public/swagger.yaml", "application/x-yaml");
    res.setStatus(200, "OK");
    return res; });
    // Có thể thêm các route khác...
}
