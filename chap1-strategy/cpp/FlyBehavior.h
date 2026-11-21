// Fly strategy family (header-only): FlyBehavior interface plus concrete strategies.
#pragma once
#include <iostream>

// Strategy interface: one swappable flying algorithm.
class FlyBehavior {
public:
    // Virtual so deleting a concrete strategy via a base pointer is well-defined.
    virtual ~FlyBehavior() = default;
    virtual void fly() const = 0;
};

// Concrete strategies; `override` makes the compiler check the signature.
class FlyWithWings : public FlyBehavior {
public:
    void fly() const override { std::cout << "I'm flying!!\n"; }
};

class FlyNoWay : public FlyBehavior {
public:
    void fly() const override { std::cout << "I can't fly\n"; }
};

class FlyRocketPowered : public FlyBehavior {
public:
    void fly() const override { std::cout << "I'm flying with a rocket!\n"; }
};
