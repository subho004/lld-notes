// DuckCall: a non-Duck Context showing strategies are reusable on their own.
#pragma once
#include <memory>
#include <utility>

#include "QuackBehavior.h"

// Context that reuses QuackBehavior without being a Duck.
class DuckCall {
public:
    DuckCall() : quackBehavior(std::make_unique<Quack>()) {}

    void performQuack() const { quackBehavior->quack(); }
    void setQuackBehavior(std::unique_ptr<QuackBehavior> qb) { quackBehavior = std::move(qb); }

private:
    // Sole ownership of the strategy, as in Duck.
    std::unique_ptr<QuackBehavior> quackBehavior;
};
