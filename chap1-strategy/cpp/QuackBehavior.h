// Quack strategy family (header-only): QuackBehavior interface plus concrete strategies.
#pragma once
#include <iostream>

// Strategy interface: one swappable quacking algorithm.
class QuackBehavior {
public:
    // Virtual so deleting a concrete strategy via a base pointer is well-defined.
    virtual ~QuackBehavior() = default;
    virtual void quack() const = 0;
};

// Concrete strategies; `override` makes the compiler check the signature.
class Quack : public QuackBehavior {
public:
    void quack() const override { std::cout << "Quack\n"; }
};

class Squeak : public QuackBehavior {
public:
    void quack() const override { std::cout << "Squeak\n"; }
};

class MuteQuack : public QuackBehavior {
public:
    void quack() const override { std::cout << "<< Silence >>\n"; }
};
