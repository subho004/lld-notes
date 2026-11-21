#include <iostream>

#include "GumballMachine2.h"

// Client for the State-pattern machine; stack-allocated since it is non-copyable but owns its states.
int main() {
    GumballMachine2 gumballMachine(5);
    std::cout << gumballMachine << "\n";

    gumballMachine.insertQuarter();
    gumballMachine.turnCrank();
    std::cout << gumballMachine << "\n";

    gumballMachine.insertQuarter();
    gumballMachine.turnCrank();
    gumballMachine.insertQuarter();
    gumballMachine.turnCrank();
    std::cout << gumballMachine << "\n";

    gumballMachine.insertQuarter();
    gumballMachine.turnCrank();
    gumballMachine.insertQuarter();
    gumballMachine.turnCrank();
    std::cout << gumballMachine << "\n";

    std::cout << "--- Refilling ---\n";
    gumballMachine.refill(5);
    std::cout << gumballMachine << "\n";

    gumballMachine.insertQuarter();
    gumballMachine.turnCrank();
    std::cout << gumballMachine << "\n";
    return 0;
}
