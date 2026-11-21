// Concrete class: Coffee supplies the brew and condiment steps of the template.
#pragma once
#include "CaffieneBeverage.h"

class Coffee : public CaffieneBeverage {
protected:
    // `override` makes the compiler check these really replace the base steps.
    void brew() override { std::cout << "Brewing coffee\n"; }
    void addCondiments() override { std::cout << "Adding sugar and milk\n"; }
};
