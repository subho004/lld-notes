#pragma once
// The "dependent" pizza store: one class that knows every concrete pizza.
#include <memory>
#include <string>

#include "Pizza.h"

// The 'before' picture: one class depends on every concrete pizza (no Factory Method).
// Chicago has no veggie pizza, so that combination returns an empty unique_ptr.
class DependentPizzaStore {
public:
    std::unique_ptr<Pizza> createPizza(const std::string& region, const std::string& type) {
        std::unique_ptr<Pizza> pizza;
        if (region == "NY") {
            if (type == "cheese") {
                pizza = std::make_unique<NYStyleCheesePizza>();
            } else if (type == "pepperoni") {
                pizza = std::make_unique<NYStylePepperoniPizza>();
            } else if (type == "clam") {
                pizza = std::make_unique<NYStyleClamPizza>();
            } else if (type == "veggie") {
                pizza = std::make_unique<NYStyleVeggiePizza>();
            }
        } else if (region == "Chicago") {
            if (type == "cheese") {
                pizza = std::make_unique<ChicagoStyleCheesePizza>();
            } else if (type == "pepperoni") {
                pizza = std::make_unique<ChicagoStylePepperoniPizza>();
            } else if (type == "clam") {
                pizza = std::make_unique<ChicagoStyleClamPizza>();
            }
        }
        return pizza;
    }
};
