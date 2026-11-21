#pragma once
// Simple Factory: SamplePizzaFactory.
#include <memory>
#include <string>

#include "Pizza.h"

// Simple Factory (not a GoF pattern): isolates the creation if/else. Unused by any
// entry point, as in the Java code; header-only so it compiles on its own.
class SamplePizzaFactory {
public:
    std::unique_ptr<Pizza> createPizza(const std::string& type) {
        std::unique_ptr<Pizza> pizza;
        if (type == "cheese") {
            pizza = std::make_unique<CheesePizza>();
        } else if (type == "pepperoni") {
            pizza = std::make_unique<PepperoniPizza>();
        } else if (type == "clam") {
            pizza = std::make_unique<ClamPizza>();
        } else if (type == "veggie") {
            pizza = std::make_unique<VeggiePizza>();
        }
        return pizza;
    }
};
