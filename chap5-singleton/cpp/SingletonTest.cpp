// Client for Singleton: two getInstance() calls must yield the same address.
#include <iostream>
#include "Singleton.h"

int main() {
    Singleton& first = Singleton::getInstance();
    Singleton& second = Singleton::getInstance();
    std::cout << "Same instance? " << std::boolalpha << (&first == &second) << "\n";
}
