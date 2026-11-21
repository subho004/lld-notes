#pragma once
#include "State.h"

class GumballMachine2;  // forward declaration: breaks the State <-> Context cycle

// SoldState.h: Concrete State, crank turned; dispense() releases a ball and picks the next state.
// Method bodies live in StateImpl.h (they need the complete GumballMachine2).
class SoldState : public State {
public:
    explicit SoldState(GumballMachine2& gumballMachine) : gumballMachine(gumballMachine) {}
    // `override` makes the compiler check each signature against State.
    void insertQuarter() override;
    void ejectQuarter() override;
    void turnCrank() override;
    void dispense() override;
    void refill() override;

private:
    GumballMachine2& gumballMachine;  // non-owning back reference
};
