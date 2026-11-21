// Server side of the remote demo: builds a GumballMachine and binds it in the
// in-process Naming registry. Usage: GumballMachineTestDrive <name> <inventory>.
#include <exception>
#include <iostream>
#include <memory>
#include <string>

#include "GumballMachine.h"

int main(int argc, char** argv) {
    if (argc - 1 < 2) {
        std::cout << "GumballMachine <name> <inventory>\n";
        return 1;
    }

    try {
        int count = std::stoi(argv[2]);
        // make_shared is required: the machine uses shared_from_this().
        auto gumballMachine = std::make_shared<GumballMachine>(argv[1], count);
        Naming::rebind(std::string("//localhost/") + argv[1], gumballMachine);
        std::cout << "Gumball machine bound at //localhost/" << argv[1] << "\n";
        std::cout << gumballMachine->toString() << "\n";
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
    }
    return 0;
}
