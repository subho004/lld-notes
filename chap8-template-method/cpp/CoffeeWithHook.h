// Concrete class CoffeeWithHook, plus the startsWithY answer parser shared by both hook subclasses.
#pragma once
#include <algorithm>
#include <cctype>
#include <string>

#include "CaffeineBeverageWithHook.h"

// Case-insensitive "answer begins with y"; takes the string by value to lowercase a copy.
inline bool startsWithY(std::string answer) {
    std::transform(answer.begin(), answer.end(), answer.begin(),
                   [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return answer.rfind("y", 0) == 0;
}

// Concrete subclass that overrides the hook to ask the user about condiments.
class CoffeeWithHook : public CaffeineBeverageWithHook {
protected:
    void brew() override { std::cout << "Dripping Coffee through filter\n"; }
    void addCondiments() override { std::cout << "Adding Sugar and Milk\n"; }

    // Overrides the hook; EOF gives "" which counts as "no".
    bool customerWantsCondiments() override {
        return startsWithY(getUserInput());
    }

private:
    std::string getUserInput() {
        return getUserInputLine("Would you like sugar and milk in your coffee (y/n)? ");
    }
};
