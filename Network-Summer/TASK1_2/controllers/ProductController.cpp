#include "ProductController.h"
#include <sstream>

Response ProductController::handle(const Request &req)
{
    if (req.getMethod() == "GET")
    {
        return listProducts(req);
    }
    else if (req.getMethod() == "POST")
    {
        return storeProduct(req);
    }
    else if (req.getMethod() == "DELETE")
    {
        return removeProductById(req);
    }
    else
    {
        Response res;
        res.setStatus(405, "Method Not Allowed");
        return res;
    }
}

Response ProductController::listProducts(const Request &req)
{
    Response res;
    auto products = this->model.all();

    std::ostringstream body;
    body << "{ \"products\": [";

    for (size_t i = 0; i < products.size(); ++i)
    {
        const auto &p = products[i];
        body << "{"
             << "\"id\": " << p.id << ", "
             << "\"name\": \"" << p.name << "\", "
             << "\"price\": " << p.price
             << "}";

        if (i < products.size() - 1)
        {
            body << ", ";
        }
    }

    body << "] }";

    res.setStatus(200, "OK");
    res.setHeader("Content-Type", "application/json");
    res.setBody(body.str());
    return res;
}

Response ProductController::storeProduct(const Request &req)
{
    auto body = req.getBodyJSON();
    Response res;

    if (body.find("name") == body.end() || body.find("price") == body.end())
    {
        res.setStatus(400, "Bad Request");
        res.setBody("Missing 'name' or 'price' in request body");
        return res;
    }

    try
    {
        std::string name = body["name"];
        double price = std::stod(body["price"]);

        model.create(name, price);

        res.setStatus(201, "Created");
        res.setHeader("Content-Type", "text/plain");
        res.setBody("Product created successfully.");
    }
    catch (...)
    {
        res.setStatus(400, "Bad Request");
        res.setHeader("Content-Type", "text/plain");
        res.setBody("Invalid 'price' value");
    }

    return res;
}

Response ProductController::removeProductById(const Request &req)
{
    auto body = req.getBodyJSON();
    Response res;

    if (body.find("id") == body.end())
    {
        res.setStatus(400, "Bad request");
        res.setBody("Missing 'id' in request body");
        return res;
    }
    try
    {
        auto products = this->model.all();
        int id = std::stoi(body["id"]);
        std::cout << "[DEBUG] id URL =" << id << endl;
        bool found = false;

        // index of product starting from 1 
        for (size_t i = 0; i < products.size(); i++)
        {
            if (id == products[i].id)
            {
                std::cout << "id=" << products[i].id << ";name=" << products[i].name << endl; 
                // Chỉ xóa bản sao của products chứ không phải trong model 
                // products[i] = products[products.size() - 1];
                // products.pop_back();
                if (this->model.removeById(i))
                {
                    found = true;
                }
            }
        }

        if (found) 
        {
            res.setStatus(200, "OK");
            res.setBody("Product removed successfully.");
        }

        else if (!found)
        {
            res.setStatus(404, "Not found");
            res.setBody("Product with id not found.");
        }

        return res;
    }
    catch (...)
    {
        res.setStatus(400, "Bad Request");
        res.setHeader("Content-Type", "text/plain");
        res.setBody("Product identifier not found");
    }

    return res;
}

Response ProductController::updateProduct(const Request &req)
{
    auto body = req.getBodyJSON();
    Response res;
    if (body.find("id") == body.end())
    {
        res.setStatus(400, "Bad request");
        res.setBody("Missing 'id' in request body");
        return res;
    }
    try
    {
        auto products = this->model.all();
        int id = std::stoi(body["id"]);
        std::cout << "[DEBUG] id URL =" << id << endl;
        bool found = false;

        // index of product starting from 1 
        for (size_t i = 0; i < products.size(); i++)
        {
            if (id == products[i].id)
            {
                std::cout << "id=" << products[i].id << ";name=" << products[i].name << endl; 
                if (this->model.update(i, body["name"], std::stod(body["price"])))
                {
                    found = true;
                }
            }
        }

        if (found) 
        {
            res.setStatus(200, "OK");
            res.setBody("Product updated successfully.");
        }

        else if (!found)
        {
            res.setStatus(404, "Not found");
            res.setBody("Product with id not found.");
        }

        return res;
    }
    catch (...)
    {
        res.setStatus(400, "Bad Request");
        res.setHeader("Content-Type", "text/plain");
        res.setBody("Product identifier not found");
    }

    return res;
}