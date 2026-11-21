// Abstract base (Template Method) with a hook; also holds the shared stdin prompt helper (header-only).
#pragma once
#include <iostream>
#include <string>

// Reads one line from stdin after printing the prompt ("" on EOF).
// `inline` allows this definition in a header included from several files.
inline std::string getUserInputLine(const std::string& prompt) {
    std::cout << prompt << std::flush;
    std::string line;
    std::getline(std::cin, line);
    if (!line.empty() && line.back() == '\r') line.pop_back();
    return line;
}

// Template Method whose prepareRecipe() contains a hook (customerWantsCondiments).
class CaffeineBeverageWithHook {
public:
    // Virtual destructor: subclasses may be deleted through a base pointer.
    virtual ~CaffeineBeverageWithHook() = default;

    void prepareRecipe() {
        boilWater();
        brew();
        pourInCup();
        if (customerWantsCondiments()) {
            addCondiments();
        }
    }

protected:
    virtual void brew() = 0;
    virtual void addCondiments() = 0;

    virtual void boilWater() { std::cout << "Boiling water\n"; }
    virtual void pourInCup() { std::cout << "Pouring into cup\n"; }

    // Hook with a default (true); subclasses may override it to change the flow.
    virtual bool customerWantsCondiments() { return true; }
};
