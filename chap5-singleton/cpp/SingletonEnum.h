// SingletonEnum: C++ stand-in for Java's enum singleton.
#pragma once
#include <iostream>

// C++ has no enum-with-methods; a Meyers singleton is the closest equivalent.
class SingletonEnum {
public:
    static SingletonEnum& INSTANCE() {
        static SingletonEnum instance;
        return instance;
    }
    SingletonEnum(const SingletonEnum&) = delete;
    SingletonEnum& operator=(const SingletonEnum&) = delete;

    void doSomething() const { std::cout << "SingletonEnum\n"; }

private:
    SingletonEnum() = default;
};
