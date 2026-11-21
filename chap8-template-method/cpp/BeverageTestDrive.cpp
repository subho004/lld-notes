// Client: runs both hook beverages through the same template method (reads y/n from stdin).
#include <iostream>

#include "CoffeeWithHook.h"
#include "TeaWithHook.h"

int main() {
    TeaWithHook teaHook;
    CoffeeWithHook coffeeHook;

    std::cout << "\nMaking tea...\n";
    teaHook.prepareRecipe();

    std::cout << "\nMaking coffee...\n";
    coffeeHook.prepareRecipe();
}
