// GumballMonitor: client of the remote proxy. Depends only on the
// GumballMachineRemote interface, so it cannot tell a stub from a local machine.
#pragma once
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "GumballMachineRemote.h"

class GumballMonitor {
    // Function-local static counter standing in for Java's identity hash.
    static int& nextId() {
        static int id = 1;
        return id;
    }
    std::shared_ptr<GumballMachineRemote> machine;
    int id;

public:
    explicit GumballMonitor(std::shared_ptr<GumballMachineRemote> m) : machine(std::move(m)), id(nextId()++) {}

    void report() {
        try {
            std::cout << "Gumball Machine: " << machine->getLocation() << "\n";
            std::cout << "Current inventory: " << machine->getCount() << " gumballs\n";
            std::cout << "Current state: " << machine->getState() << "\n";
        // A remote call can fail (checked exception in Java RMI).
        } catch (const RemoteException& e) {
            std::cerr << e.what() << "\n";
        }
    }

    // Java prints GumballMonitor@<identity hash>; use a deterministic id.
    std::string toString() const {
        std::ostringstream os;
        os << "GumballMonitor@" << std::hex << id;
        return os.str();
    }
};
