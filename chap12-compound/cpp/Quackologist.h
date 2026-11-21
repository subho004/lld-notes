// Concrete Observer: Quackologist.
#pragma once
#include <iostream>

#include "Observer.h"

// Reports each quack it hears about.
class Quackologist : public Observer {
public:
    void update(const QuackObservable& duck) override {
        std::cout << "Quackologist: " << duck.toString() << " just quacked." << std::endl;
    }
};
