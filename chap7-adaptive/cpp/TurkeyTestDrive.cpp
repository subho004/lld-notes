// Client: passes a DuckAdapter to code that only knows the Turkey interface.
#include <iostream>
#include <memory>

#include "Duck.h"
#include "DuckAdapter.h"
#include "Turkey.h"

// Takes the Turkey interface by reference, so a DuckAdapter works here too.
static void testTurkey(Turkey& turkey) {
    turkey.gobble();
    turkey.fly();
}

int main() {
    auto duck = std::make_shared<MallardDuck>();
    auto turkey = std::make_shared<WildTurkey>();
    // Shared ownership: both main and the adapter use the duck.
    std::shared_ptr<Turkey> duckAdapter = std::make_shared<DuckAdapter>(duck);

    std::cout << "The Duck says...\n";
    testTurkey(*turkey);

    std::cout << "\nThe TurkeyAdapter says...\n";
    testTurkey(*duckAdapter);
    return 0;
}
