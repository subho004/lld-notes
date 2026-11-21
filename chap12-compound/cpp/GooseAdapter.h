// Adapter: GooseAdapter.
#pragma once
#include <iostream>
#include <memory>
#include <string>

#include "Goose.h"
#include "Observable.h"
#include "Quackable.h"

// Adapter: makes a Goose look like a Quackable.
class GooseAdapter : public Quackable {
    std::shared_ptr<Goose> goose;  // the adaptee
    Observable observable;

public:
    explicit GooseAdapter(std::shared_ptr<Goose> goose)
        : goose(std::move(goose)), observable(this) {}

    void quack() override {
        goose->honk();  // translate quack() into honk()
        notifyObservers();
    }

    void registerObserver(std::shared_ptr<Observer> observer) override {
        observable.registerObserver(observer);
    }

    void notifyObservers() override { observable.notifyObservers(); }

    std::string toString() const override { return "Goose pretending to be a Duck"; }
};
