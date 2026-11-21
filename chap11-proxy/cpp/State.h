// State interface of the State pattern: one method per action the machine
// delegates to its current state. Implemented by the concrete states in States.h.
#pragma once
#include <string>

// Abstract State. The virtual destructor lets the machine delete concrete
// states through unique_ptr<State>.
class State {
public:
    virtual ~State() = default;
    virtual void insertQuarter() = 0;
    virtual void ejectQuarter() = 0;
    virtual void turnCrank() = 0;
    virtual void dispense() = 0;
    virtual void refill() = 0;
    // Description used when the machine reports its state (Java's toString).
    virtual std::string toString() const = 0;
};
