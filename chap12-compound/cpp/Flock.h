// Composite: Flock, a Quackable that holds other Quackables.
#pragma once
#include <memory>
#include <vector>

#include "Quackable.h"

// Composite: a group of Quackables that is itself a Quackable.
class Flock : public Quackable {
    // shared_ptr children: a duck (or sub-flock) can be shared and outlive the flock.
    std::vector<std::shared_ptr<Quackable>> ducks;

public:
    void add(std::shared_ptr<Quackable> duck) { ducks.push_back(std::move(duck)); }

    // Composite mechanic: delegate to each child, which may itself be a Flock.
    void quack() override {
        for (auto& duck : ducks) {
            duck->quack();
        }
    }

    // Registers on the leaf ducks, not on the flock itself.
    void registerObserver(std::shared_ptr<Observer> observer) override {
        for (auto& duck : ducks) {
            duck->registerObserver(observer);
        }
    }

    // Empty on purpose: each duck notifies its own observers.
    void notifyObservers() override {}
};
