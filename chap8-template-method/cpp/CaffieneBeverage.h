// Abstract base (Template Method) for Coffee and Tea; the name keeps the Java typo.
#pragma once
#include <iostream>

// prepareRecipe() is non-virtual (Java "final"), so subclasses cannot change the algorithm order.
class CaffieneBeverage {
public:
    // Virtual destructor: subclasses may be deleted through a base pointer.
    virtual ~CaffieneBeverage() = default;

    void prepareRecipe() {
        boilWater();
        brew();
        pourInCup();
        addCondiments();
    }

protected:
    // Protected virtuals: subclasses override the steps, outside callers cannot invoke them.
    virtual void brew() = 0;
    virtual void addCondiments() = 0;

    virtual void boilWater() { std::cout << "Boiling water\n"; }
    virtual void pourInCup() { std::cout << "Pouring into cup\n"; }
};
