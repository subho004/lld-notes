// Client for ChocolateBoiler: checks the Singleton and walks fill -> boil -> drain.
#include <iostream>
#include "ChocolateBoiler.h"

static void report(ChocolateBoiler& b) {
    std::cout << std::boolalpha << "Empty: " << b.isEmpty()
              << ", Boiled: " << b.isBoiled() << "\n";
}

int main() {
    ChocolateBoiler& boiler = ChocolateBoiler::getInstance();
    ChocolateBoiler& sameBoiler = ChocolateBoiler::getInstance();

    std::cout << "Same instance? " << std::boolalpha << (&boiler == &sameBoiler) << "\n";

    boiler.fill();
    report(boiler);
    boiler.boil();
    report(boiler);
    boiler.drain();
    report(boiler);
}
