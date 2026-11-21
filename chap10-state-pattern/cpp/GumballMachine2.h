#pragma once
#include <cstdint>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <utility>

#include "HasQuarterState.h"
#include "NoQuarterState.h"
#include "RandomSource.h"
#include "SoldOutState.h"
#include "SoldState.h"
#include "State.h"
#include "WinnerState.h"

// GumballMachine2.h: Context of the State pattern (the "after" design).
// Context. Owns all state objects; `state` is a non-owning pointer to one of them.
class GumballMachine2 {
public:
    // RandomSource is a shared_ptr because the machine passes it on to HasQuarterState.
    explicit GumballMachine2(int numberGumballs,
                             std::shared_ptr<RandomSource> randomSource = defaultRandomSource())
        : soldOutState(std::make_unique<SoldOutState>(*this)),
          noQuarterState(std::make_unique<NoQuarterState>(*this)),
          hasQuarterState(std::make_unique<HasQuarterState>(*this, std::move(randomSource))),
          soldState(std::make_unique<SoldState>(*this)),
          winnerState(std::make_unique<WinnerState>(*this)),
          // Raw pointer is fine: the unique_ptrs above outlive every use of `state`.
          state(soldOutState.get()),
          count(numberGumballs) {
        if (numberGumballs > 0) state = noQuarterState.get();
    }

    GumballMachine2(const GumballMachine2&) = delete;             // states hold references to us
    GumballMachine2& operator=(const GumballMachine2&) = delete;

    void insertQuarter() { state->insertQuarter(); }
    void ejectQuarter() { state->ejectQuarter(); }
    // Dispense is not user-triggered, so the context calls it after turnCrank.
    void turnCrank() {
        state->turnCrank();
        state->dispense();
    }
    void refill(int n) {
        count += n;
        std::cout << "The gumball machine was just refilled; its new count is: " << count << "\n";
        state->refill();
    }

    // Called back by states to perform a transition; does not take ownership.
    void setState(State* s) { state = s; }
    // Helper for states that dispense; it does not change state itself.
    void releaseBall() {
        std::cout << "A gumball comes rolling out the slot...\n";
        if (count > 0) count = count - 1;
    }

    // Getters expose the owned states as non-owning pointers for transitions.
    State* getSoldOutState() const { return soldOutState.get(); }
    State* getNoQuarterState() const { return noQuarterState.get(); }
    State* getHasQuarterState() const { return hasQuarterState.get(); }
    State* getSoldState() const { return soldState.get(); }
    State* getWinnerState() const { return winnerState.get(); }
    int getCount() const { return count; }

    std::string toString() const {
        std::ostringstream result;
        result << "\nMighty Gumball, Inc.";
        result << "\nJava-enabled Standing Gumball Model #2004";
        result << "\nInventory: " << count << " gumball";
        if (count != 1) result << "s";
        // Java prints the default Object.toString(): ClassName@hash
        result << "\nMachine is " << stateName(state) << "@" << std::hex
               << (reinterpret_cast<std::uintptr_t>(state) & 0xFFFFFFFFu) << "\n";
        return result.str();
    }

private:
    // dynamic_cast gives the runtime class name, standing in for Java's Object.toString().
    static const char* stateName(const State* s) {
        if (dynamic_cast<const SoldOutState*>(s)) return "SoldOutState";
        if (dynamic_cast<const NoQuarterState*>(s)) return "NoQuarterState";
        if (dynamic_cast<const HasQuarterState*>(s)) return "HasQuarterState";
        if (dynamic_cast<const SoldState*>(s)) return "SoldState";
        return "WinnerState";
    }

    std::unique_ptr<State> soldOutState;
    std::unique_ptr<State> noQuarterState;
    std::unique_ptr<State> hasQuarterState;
    std::unique_ptr<State> soldState;
    std::unique_ptr<State> winnerState;
    State* state;
    int count;
};

// Lets the test drive print the machine with `std::cout << machine`.
inline std::ostream& operator<<(std::ostream& os, const GumballMachine2& m) {
    return os << m.toString();
}

#include "StateImpl.h"  // inline state method bodies (need the complete GumballMachine2)
