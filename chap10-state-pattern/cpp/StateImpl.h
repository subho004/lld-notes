#pragma once
// Method bodies of the concrete states. They need the complete GumballMachine2
// type, so they live here and are included at the end of GumballMachine2.h.
#include <iostream>

#include "GumballMachine2.h"

inline void NoQuarterState::insertQuarter() {
    std::cout << "You inserted a quarter\n";
    gumballMachine.setState(gumballMachine.getHasQuarterState());
}
inline void NoQuarterState::ejectQuarter() { std::cout << "You haven't inserted a quarter\n"; }
inline void NoQuarterState::turnCrank() { std::cout << "You turned, but there's no quarter\n"; }
inline void NoQuarterState::dispense() { std::cout << "You need to pay first\n"; }
inline void NoQuarterState::refill() {}

inline void HasQuarterState::insertQuarter() { std::cout << "You can't insert another quarter\n"; }
inline void HasQuarterState::ejectQuarter() {
    std::cout << "Quarter returned\n";
    gumballMachine.setState(gumballMachine.getNoQuarterState());
}
// Winner needs a 0 draw and at least 2 balls left; otherwise normal sale.
inline void HasQuarterState::turnCrank() {
    std::cout << "You turned...\n";
    int winner = randomWinner->nextInt(10);
    if (winner == 0 && gumballMachine.getCount() > 1) {
        gumballMachine.setState(gumballMachine.getWinnerState());
    } else {
        gumballMachine.setState(gumballMachine.getSoldState());
    }
}
inline void HasQuarterState::dispense() { std::cout << "No gumball dispensed\n"; }
inline void HasQuarterState::refill() {}

inline void SoldState::insertQuarter() {
    std::cout << "Please wait, we're already giving you a gumball\n";
}
inline void SoldState::ejectQuarter() { std::cout << "Sorry, you already turned the crank\n"; }
inline void SoldState::turnCrank() {
    std::cout << "Turning twice doesn't get you another gumball!\n";
}
inline void SoldState::dispense() {
    gumballMachine.releaseBall();
    if (gumballMachine.getCount() > 0) {
        gumballMachine.setState(gumballMachine.getNoQuarterState());
    } else {
        std::cout << "Oops, out of gumballs!\n";
        gumballMachine.setState(gumballMachine.getSoldOutState());
    }
}
inline void SoldState::refill() {}

inline void SoldOutState::insertQuarter() {
    std::cout << "You can't insert a quarter, the machine is sold out\n";
}
inline void SoldOutState::ejectQuarter() {
    std::cout << "You can't eject, you haven't inserted a quarter yet\n";
}
inline void SoldOutState::turnCrank() { std::cout << "You turned, but there are no gumballs\n"; }
inline void SoldOutState::dispense() { std::cout << "No gumball dispensed\n"; }
// Only transition out of SoldOut; empty refill() in the other states is a no-op.
inline void SoldOutState::refill() { gumballMachine.setState(gumballMachine.getNoQuarterState()); }

inline void WinnerState::insertQuarter() {
    std::cout << "Please wait, we're already giving you a gumball\n";
}
inline void WinnerState::ejectQuarter() { std::cout << "Sorry, you already turned the crank\n"; }
inline void WinnerState::turnCrank() {
    std::cout << "Turning twice doesn't get you another gumball!\n";
}
// Releases the first ball, then a second one only if stock remains.
inline void WinnerState::dispense() {
    std::cout << "YOU'RE A WINNER! You get two gumballs for your quarter\n";
    gumballMachine.releaseBall();
    if (gumballMachine.getCount() == 0) {
        gumballMachine.setState(gumballMachine.getSoldOutState());
    } else {
        gumballMachine.releaseBall();
        if (gumballMachine.getCount() > 0) {
            gumballMachine.setState(gumballMachine.getNoQuarterState());
        } else {
            std::cout << "Oops, out of gumballs!\n";
            gumballMachine.setState(gumballMachine.getSoldOutState());
        }
    }
}
inline void WinnerState::refill() {}
