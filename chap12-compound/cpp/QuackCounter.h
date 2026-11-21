// Decorator: QuackCounter.
#pragma once
#include <memory>

#include "Quackable.h"

// Decorator: counts every quack of the wrapped Quackable.
class QuackCounter : public Quackable {
    std::shared_ptr<Quackable> duck;  // the wrapped component
    // C++17 inline static: one shared total, no out-of-class definition needed.
    inline static int numberOfQuacks = 0;

public:
    explicit QuackCounter(std::shared_ptr<Quackable> duck) : duck(std::move(duck)) {}

    void quack() override {
        duck->quack();  // delegate first, then add the counting behavior
        numberOfQuacks++;
    }

    static int getQuacks() { return numberOfQuacks; }

    // Pure delegation: observers end up on the wrapped duck.
    void registerObserver(std::shared_ptr<Observer> observer) override {
        duck->registerObserver(observer);
    }

    void notifyObservers() override { duck->notifyObservers(); }
};
