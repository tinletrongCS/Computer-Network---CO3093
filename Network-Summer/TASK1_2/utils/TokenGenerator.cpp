#include "TokenGenerator.h"
#include <cstdlib>
#include <ctime>

std::string TokenGenerator::generate()
{
    static const char charset[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string token;
    std::srand(std::time(nullptr));
    for (int i = 0; i < 16; ++i)
    {
        token += charset[std::rand() % (sizeof(charset) - 1)];
    }
    return token;
}