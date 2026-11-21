#pragma once
// Factory Method: PizzaStore and its regional subclasses.
#include <memory>
#include <string>

#include "Pizza.h"

// Creator in the Factory Method pattern: orderPizza() is the fixed workflow and calls the
// virtual createPizza() hook. It returns unique_ptr, so the caller owns the pizza.
class PizzaStore {
public:
    virtual ~PizzaStore() = default;

    std::unique_ptr<Pizza> orderPizza(const std::string& type) {
        std::unique_ptr<Pizza> pizza = createPizza(type);
        pizza->prepare();
        pizza->bake();
        pizza->cut();
        pizza->box();
        return pizza;
    }

protected:
    // The factory method: protected so only the store itself (and subclasses) can call it.
    // An empty unique_ptr means an unknown type; dereferencing it is undefined behavior.
    virtual std::unique_ptr<Pizza> createPizza(const std::string& type) = 0;
};

// Concrete Creator: picks the NY-style product.
class NYStylePizzaStore : public PizzaStore {
protected:
    std::unique_ptr<Pizza> createPizza(const std::string& type) override {
        std::unique_ptr<Pizza> pizza;
        if (type == "cheese") {
            pizza = std::make_unique<NYStyleCheesePizza>();
        } else if (type == "pepperoni") {
            pizza = std::make_unique<NYStylePepperoniPizza>();
        } else if (type == "clam") {
            pizza = std::make_unique<NYStyleClamPizza>();
        } else if (type == "veggie") {
            pizza = std::make_unique<NYStyleVeggiePizza>();
        }
        return pizza;
    }
};

// Concrete Creator: picks the California-style product.
class CaliforniaStylePizzaStore : public PizzaStore {
protected:
    std::unique_ptr<Pizza> createPizza(const std::string& type) override {
        std::unique_ptr<Pizza> pizza;
        if (type == "cheese") {
            pizza = std::make_unique<CaliforniaStyleCheesePizza>();
        } else if (type == "pepperoni") {
            pizza = std::make_unique<CaliforniaStylePepperoniPizza>();
        } else if (type == "clam") {
            pizza = std::make_unique<CaliforniaStyleClamPizza>();
        } else if (type == "veggie") {
            pizza = std::make_unique<CaliforniaStyleVeggiePizza>();
        }
        return pizza;
    }
};
