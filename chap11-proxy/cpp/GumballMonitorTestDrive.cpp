// Client side of the remote demo: looks machines up (receiving stubs) and
// reports on them through GumballMonitor.
#include <exception>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "GumballMachine.h"
#include "GumballMonitor.h"

// Simulation only: the Java version relies on separately started
// GumballMachineTestDrive JVMs registered with rmiregistry.
static void bindDemoMachines() {
    Naming::rebind("//localhost/santafe", std::make_shared<GumballMachine>("santafe", 112));
    Naming::rebind("//localhost/boulder", std::make_shared<GumballMachine>("boulder", 0));
    Naming::rebind("//localhost/seattle", std::make_shared<GumballMachine>("seattle", 1));
}

int main(int argc, char** argv) {
    std::vector<std::string> locations = {"santafe", "boulder", "seattle"};
    if (argc > 1) locations.assign(argv + 1, argv + argc);

    bindDemoMachines();
    // unique_ptr slots stay null for machines whose lookup fails.
    std::vector<std::unique_ptr<GumballMonitor>> monitors(locations.size());

    for (std::size_t i = 0; i < locations.size(); i++) {
        try {
            // lookup returns a GumballMachineStub (the remote proxy) as the interface.
            auto machine = Naming::lookup("//localhost/" + locations[i]);
            monitors[i] = std::make_unique<GumballMonitor>(machine);
            std::cout << monitors[i]->toString() << "\n";
        } catch (const std::exception& e) {
            std::cerr << e.what() << "\n";
        }
    }

    for (auto& monitor : monitors) {
        if (monitor) {
            monitor->report();
            std::cout << "\n";
        }
    }
    return 0;
}
