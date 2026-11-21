// Concrete Quackable: DuckCall.
#pragma once
#include <iostream>
#include <memory>
#include <string>

#include "Observable.h"
#include "Quackable.h"

// Concrete Quackable; the four duck headers differ only in sound and name.
class DuckCall : public Quackable {
    // Owned by value: the helper handles observer bookkeeping for this duck.
    Observable observable;

public:
    DuckCall() : observable(this) {}  // helper keeps a back pointer to its owner

    void quack() override {
        std::cout << "Kwak" << std::endl;
        notifyObservers();  // tell observers after every quack
    }

    void registerObserver(std::shared_ptr<Observer> observer) override {
        observable.registerObserver(observer);
    }

    void notifyObservers() override { observable.notifyObservers(); }

    std::string toString() const override { return "Duck Call"; }
};
