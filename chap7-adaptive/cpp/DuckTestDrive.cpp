// Client: passes a TurkeyAdapter to code that only knows the Duck interface.
#include <iostream>
#include <memory>

#include "Duck.h"
#include "Turkey.h"
#include "TurkeyAdapter.h"

// Takes the Duck interface by reference, so real ducks and adapters are interchangeable.
static void testDuck(Duck& duck) {
    duck.quack();
    duck.fly();
}

int main() {
    auto duck = std::make_shared<MallardDuck>();
    auto turkey = std::make_shared<WildTurkey>();
    // Shared ownership: both main and the adapter use the turkey.
    std::shared_ptr<Duck> turkeyAdapter = std::make_shared<TurkeyAdapter>(turkey);

    std::cout << "The Turkey says...\n";
    turkey->gobble();
    turkey->fly();

    std::cout << "\nThe Duck says...\n";
    testDuck(*duck);

    std::cout << "\nThe TurkeyAdapter says...\n";
    testDuck(*turkeyAdapter);
    return 0;
}
