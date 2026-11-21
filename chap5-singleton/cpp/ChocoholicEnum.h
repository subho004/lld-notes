// ChocoholicEnum: second enum-style Singleton (Meyers singleton, as C++ has no enum with methods).
#pragma once
#include <iostream>

// Singleton: private ctor + deleted copy keep exactly one object.
class ChocoholicEnum {
public:
    // Returns a reference (never an owning pointer); the static is created once, thread-safely.
    static ChocoholicEnum& INSTANCE() {
        static ChocoholicEnum instance;
        return instance;
    }
    ChocoholicEnum(const ChocoholicEnum&) = delete;
    ChocoholicEnum& operator=(const ChocoholicEnum&) = delete;

    void eatChocolate() const { std::cout << "Eating chocolate\n"; }

private:
    ChocoholicEnum() = default;
};
