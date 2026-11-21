// Adaptee: Goose, which has honk() instead of quack().
#pragma once
#include <iostream>

// Adaptee, wrapped by GooseAdapter.
class Goose {
public:
    void honk() { std::cout << "Honk" << std::endl; }
};
