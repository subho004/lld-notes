#include <iostream>

#include "GumballMachine.h"

// Client for the state-less v1 machine; same scenarios as the Java TestDrive.
int main() {
    GumballMachine gumballMachine(5);
    std::cout << gumballMachine.toString() << "\n";

    gumballMachine.insertQuarter();
    gumballMachine.turnCrank();
    std::cout << gumballMachine.toString() << "\n";

    gumballMachine.insertQuarter();
    gumballMachine.ejectQuarter();
    gumballMachine.turnCrank();
    std::cout << gumballMachine.toString() << "\n";

    gumballMachine.insertQuarter();
    gumballMachine.turnCrank();
    gumballMachine.insertQuarter();
    gumballMachine.turnCrank();
    gumballMachine.ejectQuarter();
    std::cout << gumballMachine.toString() << "\n";

    gumballMachine.insertQuarter();
    gumballMachine.insertQuarter();
    gumballMachine.turnCrank();
    gumballMachine.insertQuarter();
    gumballMachine.turnCrank();
    gumballMachine.insertQuarter();
    gumballMachine.turnCrank();
    std::cout << gumballMachine.toString() << "\n";
    return 0;
}
