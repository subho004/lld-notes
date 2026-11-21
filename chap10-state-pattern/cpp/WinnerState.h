#pragma once
#include "State.h"

class GumballMachine2;  // forward declaration: breaks the State <-> Context cycle

// WinnerState.h: Concrete State, 1-in-10 winner, dispenses two gumballs for one quarter.
// Method bodies live in StateImpl.h (they need the complete GumballMachine2).
class WinnerState : public State {
public:
    explicit WinnerState(GumballMachine2& gumballMachine) : gumballMachine(gumballMachine) {}
    // `override` makes the compiler check each signature against State.
    void insertQuarter() override;
    void ejectQuarter() override;
    void turnCrank() override;
    void dispense() override;
    void refill() override;

private:
    GumballMachine2& gumballMachine;  // non-owning back reference
};
