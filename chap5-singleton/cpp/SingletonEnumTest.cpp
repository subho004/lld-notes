// Client for SingletonEnum: calls the method and compares addresses.
#include <iostream>
#include "SingletonEnum.h"

int main() {
    SingletonEnum::INSTANCE().doSomething();
    SingletonEnum& another = SingletonEnum::INSTANCE();
    std::cout << "Same instance? " << std::boolalpha
              << (&SingletonEnum::INSTANCE() == &another) << "\n";
}
