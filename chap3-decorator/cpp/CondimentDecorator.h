// Decorator side of the pattern: abstract CondimentDecorator and Mocha, Soy, Whip.
#pragma once

#include <memory>
#include <string>
#include <utility>

#include "Beverage.h"

// Abstract Decorator: is-a Beverage and has-a Beverage. It owns the wrapped drink via
// unique_ptr, so destroying the outermost decorator frees the whole chain.
class CondimentDecorator : public Beverage {
public:
    explicit CondimentDecorator(std::unique_ptr<Beverage> b) : beverage(std::move(b)) {}

    // Pure virtual with override: each decorator must extend the wrapped description.
    std::string getDescription() const override = 0;

    bool hasMilk() const override { return false; }
    bool hasSoy() const override { return false; }
    bool hasMocha() const override { return false; }
    bool hasWhip() const override { return false; }

    // Forward size inward so the innermost drink's size is seen by every decorator.
    Size getSize() const override { return beverage->getSize(); }

protected:
    std::unique_ptr<Beverage> beverage;
};

// Concrete Decorators. Inheriting constructors avoid repeating the wrapping constructor;
// cost() delegates inward and adds this decorator's own price.
class Mocha : public CondimentDecorator {
public:
    using CondimentDecorator::CondimentDecorator;
    std::string getDescription() const override { return beverage->getDescription() + ", Mocha"; }
    double cost() const override { return 0.20 + beverage->cost(); }
};

// Soy is priced by the wrapped drink's size.
class Soy : public CondimentDecorator {
public:
    using CondimentDecorator::CondimentDecorator;
    std::string getDescription() const override { return beverage->getDescription() + ", Soy"; }
    double cost() const override {
        double c = beverage->cost();
        if (beverage->getSize() == Size::TALL) {
            c += 0.10;
        } else if (beverage->getSize() == Size::GRANDE) {
            c += 0.15;
        } else if (beverage->getSize() == Size::VENTI) {
            c += 0.20;
        }
        return c;
    }
};

class Whip : public CondimentDecorator {
public:
    using CondimentDecorator::CondimentDecorator;
    std::string getDescription() const override { return beverage->getDescription() + ", Whip"; }
    double cost() const override { return 0.10 + beverage->cost(); }
};
