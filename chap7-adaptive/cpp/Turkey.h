// Turkey: interface incompatible with Duck, plus WildTurkey, a concrete Turkey (the adaptee).
#pragma once
#include <iostream>

// Abstract interface; the virtual destructor makes delete-through-base safe.
class Turkey {
public:
    virtual ~Turkey() = default;
    virtual void gobble() = 0;
    virtual void fly() = 0;
};

// Concrete Turkey, wrapped by TurkeyAdapter.
class WildTurkey : public Turkey {
public:
    void gobble() override { std::cout << "Gobble gobble\n"; }
    void fly() override { std::cout << "I'm flying a short distance\n"; }
};
