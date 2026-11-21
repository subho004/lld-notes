#pragma once
#include <memory>
#include <utility>

#include "RandomSource.h"
#include "State.h"

class GumballMachine2;  // forward declaration: breaks the State <-> Context cycle

// HasQuarterState.h: Concrete State, quarter inserted; turning the crank may pick the winner path.
// Method bodies live in StateImpl.h (they need the complete GumballMachine2).
class HasQuarterState : public State {
public:
    HasQuarterState(GumballMachine2& gumballMachine, std::shared_ptr<RandomSource> randomWinner)
        : gumballMachine(gumballMachine), randomWinner(std::move(randomWinner)) {}
    // `override` makes the compiler check each signature against State.
    void insertQuarter() override;
    void ejectQuarter() override;
    void turnCrank() override;
    void dispense() override;
    void refill() override;

private:
    GumballMachine2& gumballMachine;  // non-owning back reference
    // shared_ptr: the same source is shared with the context that created it.
    std::shared_ptr<RandomSource> randomWinner;
};
