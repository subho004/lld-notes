// Duck (Context) with subclasses MallardDuck and ModelDuck, in one header.
#pragma once
#include <iostream>
#include <memory>
#include <utility>

#include "FlyBehavior.h"
#include "QuackBehavior.h"

// Context: owns its fly/quack strategies and delegates to them.
class Duck {
public:
    // Default strategies, as in the Java base constructor.
    Duck() : flyBehavior(std::make_unique<FlyWithWings>()),
             quackBehavior(std::make_unique<Quack>()) {}
    // Virtual: ducks are deleted through std::unique_ptr<Duck>.
    virtual ~Duck() = default;

    // Pure virtual: varies per subclass, so Duck is abstract.
    virtual void display() const = 0;

    // Delegation to the strategy objects.
    void performFly() const { flyBehavior->fly(); }
    void performQuack() const { quackBehavior->quack(); }
    void swim() const { std::cout << "All ducks float, even decoys!\n"; }

    // Setters take ownership via std::move, allowing runtime swaps.
    void setFlyBehavior(std::unique_ptr<FlyBehavior> fb) { flyBehavior = std::move(fb); }
    void setQuackBehavior(std::unique_ptr<QuackBehavior> qb) { quackBehavior = std::move(qb); }

protected:
    // unique_ptr: the duck is the sole owner of its strategies.
    std::unique_ptr<FlyBehavior> flyBehavior;
    std::unique_ptr<QuackBehavior> quackBehavior;
};

// Concrete context: keeps the default strategies.
class MallardDuck : public Duck {
public:
    void display() const override { std::cout << "I'm a real Mallard duck\n"; }
};

// Concrete context: starts flightless; a rocket can be set at runtime.
class ModelDuck : public Duck {
public:
    ModelDuck() {
        flyBehavior = std::make_unique<FlyNoWay>();
        quackBehavior = std::make_unique<Quack>();
    }
    void display() const override { std::cout << "I'm a model duck\n"; }
};
