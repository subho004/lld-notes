#pragma once
// Abstract Factory: IngredientFactory and the regional factories.
#include <memory>
#include <vector>

#include "Ingredients.h"

// Abstract Factory interface. Ingredients are returned by unique_ptr: the factory
// hands ownership to the pizza. Virtual destructor allows deletion via shared_ptr/base.
class IngredientFactory {
public:
    virtual ~IngredientFactory() = default;
    virtual std::unique_ptr<Dough> createDough() = 0;
    virtual std::unique_ptr<Sauce> createSauce() = 0;
    virtual std::unique_ptr<Cheese> createCheese() = 0;
    virtual std::vector<std::unique_ptr<Veggies>> createVeggies() = 0;
    virtual std::unique_ptr<Pepperoni> createPepperoni() = 0;
    virtual std::unique_ptr<Clams> createClam() = 0;
};

// Concrete Factory for the Chicago family.
class ChicagoPizzaIngredientFactory : public IngredientFactory {
public:
    std::unique_ptr<Dough> createDough() override { return std::make_unique<ThickCrustDough>(); }
    std::unique_ptr<Sauce> createSauce() override { return std::make_unique<PlumTomatoSauce>(); }
    std::unique_ptr<Cheese> createCheese() override { return std::make_unique<MozzarellaCheese>(); }
    std::vector<std::unique_ptr<Veggies>> createVeggies() override {
        std::vector<std::unique_ptr<Veggies>> v;
        v.push_back(std::make_unique<Spinach>());
        v.push_back(std::make_unique<Eggplant>());
        v.push_back(std::make_unique<BlackOlives>());
        return v;
    }
    std::unique_ptr<Pepperoni> createPepperoni() override { return std::make_unique<SlicedPepperoni>(); }
    std::unique_ptr<Clams> createClam() override { return std::make_unique<FrozenClams>(); }
};

// Concrete Factory for the New York family.
class NYPizzaIngredientFactory : public IngredientFactory {
public:
    std::unique_ptr<Dough> createDough() override { return std::make_unique<ThinCrustDough>(); }
    std::unique_ptr<Sauce> createSauce() override { return std::make_unique<MarinaraSauce>(); }
    std::unique_ptr<Cheese> createCheese() override { return std::make_unique<ReggianoCheese>(); }
    std::vector<std::unique_ptr<Veggies>> createVeggies() override {
        std::vector<std::unique_ptr<Veggies>> v;
        v.push_back(std::make_unique<Garlic>());
        v.push_back(std::make_unique<Onion>());
        v.push_back(std::make_unique<Mushroom>());
        v.push_back(std::make_unique<RedPepper>());
        return v;
    }
    std::unique_ptr<Pepperoni> createPepperoni() override { return std::make_unique<SlicedPepperoni>(); }
    std::unique_ptr<Clams> createClam() override { return std::make_unique<FreshClams>(); }
};
