#pragma once

// State.h: State interface of the pattern (Java: `interface State`).
// Virtual destructor so deleting a concrete state through State* (via unique_ptr) is safe.
class State {
public:
    virtual ~State() = default;
    virtual void insertQuarter() = 0;
    virtual void ejectQuarter() = 0;
    virtual void turnCrank() = 0;
    virtual void dispense() = 0;
    virtual void refill() = 0;
};
