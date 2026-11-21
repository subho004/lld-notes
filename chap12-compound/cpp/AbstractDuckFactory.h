// Abstract Factory interface: creates ducks without exposing their concrete types.
// Products are shared_ptr so decorators and flocks can share them.
#pragma once
#include <memory>

#include "Quackable.h"

class AbstractDuckFactory {
public:
    // Virtual destructor: factories are deleted through this base pointer.
    virtual ~AbstractDuckFactory() = default;
    virtual std::shared_ptr<Quackable> createMallardDuck() = 0;
    virtual std::shared_ptr<Quackable> createRedheadDuck() = 0;
    virtual std::shared_ptr<Quackable> createDuckCall() = 0;
    virtual std::shared_ptr<Quackable> createRubberDuck() = 0;
};
