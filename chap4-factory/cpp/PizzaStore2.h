#pragma once
// Factory Method + Abstract Factory: PizzaStore2 and its regional stores.
#include <memory>
#include <string>

#include "IngredientFactory.h"
#include "Pizza2.h"

// Creator combining Factory Method (createPizza) with Abstract Factory (the ingredient
// factory is passed to each pizza). Caller owns the returned pizza via unique_ptr.
class PizzaStore2 {
public:
    virtual ~PizzaStore2() = default;

    std::unique_ptr<Pizza2> orderPizza(const std::string& type) {
        std::unique_ptr<Pizza2> pizza = createPizza(type);
        pizza->prepare();
        pizza->bake();
        pizza->cut();
        pizza->box();
        return pizza;
    }

protected:
    virtual std::unique_ptr<Pizza2> createPizza(const std::string& type) = 0;

    // C++ factoring of the if/else chain Java repeats in each regional store. The
    // shared_ptr is copied into the pizza, which keeps the factory alive while it uses it.
    // Shared body of the two regional stores (they differ only in factory and name prefix).
    static std::unique_ptr<Pizza2> createWith(std::shared_ptr<IngredientFactory> f,
                                              const std::string& region,
                                              const std::string& item) {
        std::unique_ptr<Pizza2> pizza;
        if (item == "cheese") {
            pizza = std::make_unique<CheesePizza2>(f);
            pizza->setName(region + " Style Cheese Pizza");
        } else if (item == "veggie") {
            pizza = std::make_unique<VeggiePizza2>(f);
            pizza->setName(region + " Style Veggie Pizza");
        } else if (item == "pepperoni") {
            pizza = std::make_unique<PepperoniPizza2>(f);
            pizza->setName(region + " Style Pepperoni Pizza");
        } else if (item == "clam") {
            pizza = std::make_unique<ClamPizza2>(f);
            pizza->setName(region + " Style Clam Pizza");
        }
        return pizza;
    }
};

// Concrete Creator: injects a fresh NY ingredient factory.
class NYPizzaStore2 : public PizzaStore2 {
protected:
    std::unique_ptr<Pizza2> createPizza(const std::string& item) override {
        return createWith(std::make_shared<NYPizzaIngredientFactory>(), "New York", item);
    }
};

// Concrete Creator: injects a fresh Chicago ingredient factory.
class ChicagoPizzaStore2 : public PizzaStore2 {
protected:
    std::unique_ptr<Pizza2> createPizza(const std::string& item) override {
        return createWith(std::make_shared<ChicagoPizzaIngredientFactory>(), "Chicago", item);
    }
};
