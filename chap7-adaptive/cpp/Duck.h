// Duck: target interface the client expects, plus MallardDuck, a concrete Duck.
#pragma once
#include <iostream>

// Abstract target interface; the virtual destructor makes delete-through-base safe.
class Duck {
public:
    virtual ~Duck() = default;
    virtual void quack() = 0;
    virtual void fly() = 0;
};

// Concrete Duck; also the adaptee wrapped by DuckAdapter.
class MallardDuck : public Duck {
public:
    void quack() override { std::cout << "Quack\n"; }
    void fly() override { std::cout << "I'm flying\n"; }
};
