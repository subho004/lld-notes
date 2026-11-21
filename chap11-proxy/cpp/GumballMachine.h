// GumballMachine: Real Subject of the remote proxy and Context of the State
// pattern. Delegates actions to its current State.
#pragma once
#include <iostream>
#include <memory>
#include <string>

#include "GumballMachineRemote.h"
#include "State.h"

// enable_shared_from_this lets makeStub() hand the stub a shared_ptr to this
// machine, so the stub keeps it alive. Must be created with make_shared.
class GumballMachine : public GumballMachineRemote, public std::enable_shared_from_this<GumballMachine> {
    // The machine owns its states; states hold a plain back-pointer
    // (the Java field is `transient`), so there is no ownership cycle.
    std::unique_ptr<State> soldOutState;
    std::unique_ptr<State> noQuarterState;
    std::unique_ptr<State> hasQuarterState;
    std::unique_ptr<State> soldState;
    std::unique_ptr<State> winnerState;

    // Non-owning pointer to whichever owned state is current.
    State* state = nullptr;
    int count = 0;
    std::string location;

public:
    GumballMachine(std::string location, int numberGumballs);  // defined in States.h

    // Remote proxy factory: callers get a stub wrapping this machine.
    std::shared_ptr<GumballMachineRemote> makeStub() override {
        return std::make_shared<GumballMachineStub>(shared_from_this());
    }

    void insertQuarter() { state->insertQuarter(); }
    void ejectQuarter() { state->ejectQuarter(); }
    // Delegation to the current State; dispense() runs after the state change.
    void turnCrank() {
        state->turnCrank();
        state->dispense();
    }

    void refill(int n) {
        count += n;
        std::cout << "The gumball machine was just refilled; its new count is: " << count << "\n";
        state->refill();
    }

    void setState(State* s) { state = s; }

    void releaseBall() {
        std::cout << "A gumball comes rolling out the slot...\n";
        if (count > 0) count = count - 1;
    }

    std::string getLocation() override { return location; }
    int getCount() override { return count; }
    // Remote getState() returns the description by value (see GumballMachineRemote.h).
    std::string getState() override { return state->toString(); }

    State* getSoldOutState() { return soldOutState.get(); }
    State* getNoQuarterState() { return noQuarterState.get(); }
    State* getHasQuarterState() { return hasQuarterState.get(); }
    State* getSoldState() { return soldState.get(); }
    State* getWinnerState() { return winnerState.get(); }

    std::string toString() {
        std::string result;
        result += "\nMighty Gumball, Inc.";
        result += "\nJava-enabled Standing Gumball Model #2004";
        result += "\nInventory: " + std::to_string(count) + " gumball";
        if (count != 1) result += "s";
        result += "\nMachine is " + state->toString() + "\n";
        return result;
    }
};

#include "States.h"
