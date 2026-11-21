// Component side of the Decorator pattern: Beverage, PlainBeverage and the four concrete coffees.
#pragma once

#include <string>

#include "Size.h"

// Component: common interface for plain coffees and condiment decorators.
class Beverage {
public:
    // Virtual so deleting a decorated drink through Beverage* frees the whole chain.
    virtual ~Beverage() = default;

    virtual Size getSize() const { return size; }
    void setSize(Size s) { size = s; }

    // Base cost covers only built-in condiment flags; concrete coffees add their own price.
    virtual double cost() const {
        double condimentCost = 0;
        if (hasMilk()) condimentCost += 0.10;
        if (hasSoy()) condimentCost += 0.15;
        if (hasMocha()) condimentCost += 0.20;
        if (hasWhip()) condimentCost += 0.25;
        return condimentCost;
    }

    virtual bool hasMilk() const = 0;
    virtual bool hasSoy() const = 0;
    virtual bool hasMocha() const = 0;
    virtual bool hasWhip() const = 0;

    virtual std::string getDescription() const { return toString(size) + " " + description; }

protected:
    // protected (Java's package-private field) so subclasses can set them.
    std::string description = "Unknown Beverage";
    Size size = Size::TALL;
};

// Helper for the concrete coffees: no built-in condiment flags.
class PlainBeverage : public Beverage {
public:
    bool hasMilk() const override { return false; }
    bool hasSoy() const override { return false; }
    bool hasMocha() const override { return false; }
    bool hasWhip() const override { return false; }
};

// Concrete Components: each sets its description and adds its own price.
class DarkRoast : public PlainBeverage {
public:
    DarkRoast() { description = "Dark Roast Coffee"; }
    double cost() const override { return 0.99 + Beverage::cost(); }
};

class Decaf : public PlainBeverage {
public:
    Decaf() { description = "Decaf Coffee"; }
    double cost() const override { return 1.05 + Beverage::cost(); }
};

class Expresso : public PlainBeverage {
public:
    Expresso() { description = "Expresso"; }
    double cost() const override { return 1.99 + Beverage::cost(); }
};

class HouseBlend : public PlainBeverage {
public:
    HouseBlend() { description = "House Blend Coffee"; }
    double cost() const override { return 0.89 + Beverage::cost(); }
};
