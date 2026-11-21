// Observer pattern helper: Observable, owned by value by each duck.
#pragma once
#include <memory>
#include <vector>

#include "Observer.h"
#include "QuackObservable.h"

// Helper every duck owns by value and delegates observer handling to.
class Observable : public QuackObservable {
    // weak_ptr: the subject never owns its observers, so no shared_ptr cycle can form.
    std::vector<std::weak_ptr<Observer>> observers;
    const QuackObservable* duck;  // non-owning back pointer to the owner

public:
    explicit Observable(const QuackObservable* duck) : duck(duck) {}
    // Copying is deleted so the back pointer cannot dangle or point at another duck.
    Observable(const Observable&) = delete;
    Observable& operator=(const Observable&) = delete;

    void registerObserver(std::shared_ptr<Observer> observer) override {
        observers.push_back(observer);
    }

    void notifyObservers() override {
        for (auto& weak : observers) {
            // lock() fails if the observer was destroyed; such entries are skipped.
            if (auto observer = weak.lock()) {
                observer->update(*duck);
            }
        }
    }
};
