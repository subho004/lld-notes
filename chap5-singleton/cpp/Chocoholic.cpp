// Client for ChocoholicEnum: compares addresses to prove a single instance.
#include <iostream>
#include "ChocoholicEnum.h"

int main() {
    ChocoholicEnum::INSTANCE().eatChocolate();
    ChocoholicEnum& another = ChocoholicEnum::INSTANCE();
    std::cout << "Same instance? " << std::boolalpha
              << (&ChocoholicEnum::INSTANCE() == &another) << "\n";
}
