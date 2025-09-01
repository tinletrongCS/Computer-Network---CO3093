#include "ProductModel.h"

std::vector<Product> ProductModel::products = {
    {1, "Laptop", 999.99},
    {2, "Smartphone", 599.49},
    {3, "Headphones", 149.99}};

int ProductModel::nextId = 4;