#pragma once
#include <iostream>
#include <sstream>
#include <string>

// GumballMachine.h: the "before" design (no State pattern). Header-only for simplicity.
// First, state-less design: every action is an if/else over an int state.
class GumballMachine {
public:
    // constexpr statics replace Java's `static final int` state ids.
    static constexpr int SOLD_OUT = 0;
    static constexpr int NO_QUARTER = 1;
    static constexpr int HAS_QUARTER = 2;
    static constexpr int SOLD = 3;

    explicit GumballMachine(int count) : state(SOLD_OUT), count(count) {
        if (count > 0) state = NO_QUARTER;
    }

    void insertQuarter() {
        if (state == HAS_QUARTER) {
            std::cout << "You can't insert another quarter\n";
        } else if (state == NO_QUARTER) {
            state = HAS_QUARTER;
            std::cout << "You inserted a quarter\n";
        } else if (state == SOLD_OUT) {
            std::cout << "You can't insert a quarter, the machine is sold out\n";
        } else if (state == SOLD) {
            std::cout << "Please wait, we're already giving you a gumball\n";
        }
    }

    void ejectQuarter() {
        if (state == HAS_QUARTER) {
            std::cout << "Quarter returned\n";
            state = NO_QUARTER;
        } else if (state == NO_QUARTER) {
            std::cout << "You haven't inserted a quarter\n";
        } else if (state == SOLD_OUT) {
            std::cout << "You can't eject, you haven't inserted a quarter yet\n";
        } else if (state == SOLD) {
            std::cout << "Sorry, you already turned the crank\n";
        }
    }

    void turnCrank() {
        if (state == SOLD) {
            std::cout << "Turning twice doesn't get you another gumball!\n";
        } else if (state == NO_QUARTER) {
            std::cout << "You turned but there's no quarter\n";
        } else if (state == SOLD_OUT) {
            std::cout << "You turned, but there are no gumballs\n";
        } else if (state == HAS_QUARTER) {
            std::cout << "You turned...\n";
            state = SOLD;
            dispense();
        }
    }

    // Each method re-checks `state`; adding a state means editing all of them.
    void dispense() {
        if (state == SOLD) {
            std::cout << "A gumball comes rolling out the slot\n";
            count = count - 1;
            if (count == 0) {
                std::cout << "Oops, out of gumballs!\n";
                state = SOLD_OUT;
            } else {
                state = NO_QUARTER;
            }
        } else if (state == NO_QUARTER) {
            std::cout << "You need to pay first\n";
        } else if (state == SOLD_OUT) {
            std::cout << "No gumballs dispensed\n";
        } else if (state == HAS_QUARTER) {
            std::cout << "No gumball dispensed\n";
        }
    }

    // const: only reads the machine; output matches the Java toString().
    std::string toString() const {
        std::ostringstream result;
        result << "\nMighty Gumball, Inc.";
        result << "\nJava-enabled Standing Gumball Model #2004";
        result << "\nInventory: " << count << " gumball";
        if (count != 1) result << "s";
        result << "\n";
        switch (state) {
            case SOLD_OUT: result << "Machine is sold out"; break;
            case NO_QUARTER: result << "Machine is waiting for quarter"; break;
            case HAS_QUARTER: result << "Machine is waiting for turn of crank"; break;
            case SOLD: result << "Gumball is on its way!"; break;
            default: break;
        }
        result << "\n";
        return result.str();
    }

private:
    int state;
    int count;
};
