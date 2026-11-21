// Concrete State classes (NoQuarter, HasQuarter, Sold, Winner, SoldOut) and the
// out-of-line GumballMachine constructor. Each state moves the machine to the
// next state via setState(). Header-only; included at the end of GumballMachine.h.
#pragma once
#include <iostream>
#include <random>
#include <string>

#include "GumballMachine.h"
#include "State.h"

// Concrete State: idle, waiting for a quarter.
// The raw pointer to the machine is a non-owning back-reference; the machine owns the state.
class NoQuarterState : public State {
    GumballMachine* gumballMachine;

public:
    explicit NoQuarterState(GumballMachine* m) : gumballMachine(m) {}
    void insertQuarter() override {
        std::cout << "You inserted a quarter\n";
        gumballMachine->setState(gumballMachine->getHasQuarterState());
    }
    void ejectQuarter() override { std::cout << "You haven't inserted a quarter\n"; }
    void turnCrank() override { std::cout << "You turned, but there's no quarter\n"; }
    void dispense() override { std::cout << "You need to pay first\n"; }
    void refill() override {}
    std::string toString() const override { return "waiting for quarter"; }
};

// Concrete State: quarter inserted; crank may be turned.
class HasQuarterState : public State {
    GumballMachine* gumballMachine;
    // Java seeds with currentTimeMillis(); a different (fixed) generator is used here.
    std::mt19937 randomWinner{42};

public:
    explicit HasQuarterState(GumballMachine* m) : gumballMachine(m) {}
    void insertQuarter() override { std::cout << "You can't insert another quarter\n"; }
    void ejectQuarter() override {
        std::cout << "Quarter returned\n";
        gumballMachine->setState(gumballMachine->getNoQuarterState());
    }
    void turnCrank() override {
        std::cout << "You turned...\n";
        // A winner needs at least 2 gumballs left to pay out.
        int winner = static_cast<int>(randomWinner() % 10);
        if (winner == 0 && gumballMachine->getCount() > 1) {
            gumballMachine->setState(gumballMachine->getWinnerState());
        } else {
            gumballMachine->setState(gumballMachine->getSoldState());
        }
    }
    void dispense() override { std::cout << "No gumball dispensed\n"; }
    void refill() override {}
    std::string toString() const override { return "waiting for turn of crank"; }
};

// Concrete State: crank turned, dispensing one gumball.
class SoldState : public State {
    GumballMachine* gumballMachine;

public:
    explicit SoldState(GumballMachine* m) : gumballMachine(m) {}
    void insertQuarter() override { std::cout << "Please wait, we're already giving you a gumball\n"; }
    void ejectQuarter() override { std::cout << "Sorry, you already turned the crank\n"; }
    void turnCrank() override { std::cout << "Turning twice doesn't get you another gumball!\n"; }
    void dispense() override {
        gumballMachine->releaseBall();
        if (gumballMachine->getCount() > 0) {
            gumballMachine->setState(gumballMachine->getNoQuarterState());
        } else {
            std::cout << "Oops, out of gumballs!\n";
            gumballMachine->setState(gumballMachine->getSoldOutState());
        }
    }
    void refill() override {}
    std::string toString() const override { return "dispensing a gumball"; }
};

// Concrete State: lucky draw, dispensing two gumballs.
class WinnerState : public State {
    GumballMachine* gumballMachine;

public:
    explicit WinnerState(GumballMachine* m) : gumballMachine(m) {}
    void insertQuarter() override { std::cout << "Please wait, we're already giving you a gumball\n"; }
    void ejectQuarter() override { std::cout << "Sorry, you already turned the crank\n"; }
    void turnCrank() override { std::cout << "Turning twice doesn't get you another gumball!\n"; }
    void dispense() override {
        std::cout << "YOU'RE A WINNER! You get two gumballs for your quarter\n";
        gumballMachine->releaseBall();
        if (gumballMachine->getCount() == 0) {
            gumballMachine->setState(gumballMachine->getSoldOutState());
        } else {
            gumballMachine->releaseBall();
            if (gumballMachine->getCount() > 0) {
                gumballMachine->setState(gumballMachine->getNoQuarterState());
            } else {
                std::cout << "Oops, out of gumballs!\n";
                gumballMachine->setState(gumballMachine->getSoldOutState());
            }
        }
    }
    void refill() override {}
    std::string toString() const override {
        return "dispensing two gumballs for your quarter, because YOU'RE A WINNER!";
    }
};

// Concrete State: no gumballs left; only refill() leaves it.
class SoldOutState : public State {
    GumballMachine* gumballMachine;

public:
    explicit SoldOutState(GumballMachine* m) : gumballMachine(m) {}
    void insertQuarter() override { std::cout << "You can't insert a quarter, the machine is sold out\n"; }
    void ejectQuarter() override { std::cout << "You can't eject, you haven't inserted a quarter yet\n"; }
    void turnCrank() override { std::cout << "You turned, but there are no gumballs\n"; }
    void dispense() override { std::cout << "No gumball dispensed\n"; }
    void refill() override { gumballMachine->setState(gumballMachine->getNoQuarterState()); }
    std::string toString() const override { return "sold out"; }
};

// Defined here (after the states are complete types) because GumballMachine.h
// only sees State; 'inline' keeps this header-only definition ODR-safe.
inline GumballMachine::GumballMachine(std::string loc, int numberGumballs)
    : soldOutState(std::make_unique<SoldOutState>(this)),
      noQuarterState(std::make_unique<NoQuarterState>(this)),
      hasQuarterState(std::make_unique<HasQuarterState>(this)),
      soldState(std::make_unique<SoldState>(this)),
      winnerState(std::make_unique<WinnerState>(this)),
      count(numberGumballs),
      location(std::move(loc)) {
    // Initial state: sold out when empty, otherwise waiting for a quarter.
    state = numberGumballs > 0 ? noQuarterState.get() : soldOutState.get();
}
