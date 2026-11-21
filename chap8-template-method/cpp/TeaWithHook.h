// Concrete class TeaWithHook: overrides the condiment hook to ask the user about lemon.
#pragma once
#include <string>

#include "CoffeeWithHook.h"

// Concrete subclass; reuses startsWithY from CoffeeWithHook.h.
class TeaWithHook : public CaffeineBeverageWithHook {
protected:
    void brew() override { std::cout << "Steeping the tea\n"; }
    void addCondiments() override { std::cout << "Adding Lemon\n"; }

    // Overrides the hook from the base class; EOF counts as "no".
    bool customerWantsCondiments() override {
        return startsWithY(getUserInput());
    }

private:
    std::string getUserInput() {
        return getUserInputLine("Would you like lemon with your tea (y/n)? ");
    }
};
