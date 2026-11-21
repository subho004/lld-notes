// Concrete class: Tea supplies the brew and condiment steps of the template.
#pragma once
#include "CaffieneBeverage.h"

class Tea : public CaffieneBeverage {
protected:
    // `override` makes the compiler check these really replace the base steps.
    void brew() override { std::cout << "Steeping tea bag\n"; }
    void addCondiments() override { std::cout << "Adding lemon\n"; }
};
