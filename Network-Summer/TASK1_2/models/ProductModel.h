#pragma once
#include "BaseModel.h"
#include <vector>
#include <string>
#include <algorithm>

struct Product
{
    int id;
    std::string name;
    double price;
};

class ProductModel : public BaseModel
{
private:
    static std::vector<Product> products;
    static int nextId;

public:
    ProductModel() {}

    std::vector<Product> all()
    {
        return products;
    }

    bool create(const std::string &name, double price)
    {
        products.push_back({nextId++, name, price});
        return true;
    }

    bool removeById(size_t index)
    {
        if (index < 0 || index > products.size()) return false;
        products[index] = products[products.size() - 1];
        products.pop_back();
        return true;
    }

    bool update(size_t index, const std::string &name, double price)
    {
        if (index < 0 || index > this->products.size()) return false;
        this->products[index].name = name;
        this->products[index].price = price;
        return true;
    }
};