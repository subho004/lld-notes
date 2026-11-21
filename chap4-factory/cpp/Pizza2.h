#pragma once
// Abstract Factory version of Pizza: Pizza2 and the ingredient-driven pizzas.
// A Pizza2 owns the ingredients its factory created (unique_ptr) and shares
// the factory itself with the store that built it (shared_ptr).
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "IngredientFactory.h"

// Abstract product. prepare() is pure virtual: each subclass chooses which ingredients
// to request from its factory. Ingredient members stay empty until then.
class Pizza2 {
public:
    virtual ~Pizza2() = default;

    virtual void prepare() = 0;
    virtual void bake() { std::cout << "Bake for 25 minutes at 350\n"; }
    virtual void cut() { std::cout << "Cutting the pizza into diagonal slices\n"; }
    virtual void box() { std::cout << "Place pizza in official PizzaStore box\n"; }
    void setName(const std::string& n) { name = n; }
    std::string getName() const { return name; }

    // Skips ingredients that have not been created (null pointers / empty vector).
    std::string toString() const {
        std::string result;
        result += "---- " + name + " ----\n";
        if (dough) result += dough->toString() + "\n";
        if (sauce) result += sauce->toString() + "\n";
        if (cheese) result += cheese->toString() + "\n";
        if (!veggies.empty()) {
            result += veggiesToString() + "\n";
        }
        if (pepperoni) result += pepperoni->toString() + "\n";
        if (clams) result += clams->toString() + "\n";
        return result;
    }

protected:
    std::string veggiesToString() const {
        std::string s;
        for (std::size_t i = 0; i < veggies.size(); i++) {
            s += veggies[i]->toString();
            if (i + 1 < veggies.size()) s += ", ";
        }
        return s;
    }

    std::string name;
    std::unique_ptr<Dough> dough;
    std::unique_ptr<Sauce> sauce;
    std::vector<std::unique_ptr<Veggies>> veggies;
    std::unique_ptr<Cheese> cheese;
    std::unique_ptr<Pepperoni> pepperoni;
    std::unique_ptr<Clams> clams;
};

// Lets `std::cout << *pizza` mirror Java's implicit toString(); inline for header-only use.
inline std::ostream& operator<<(std::ostream& os, const Pizza2& p) {
    return os << p.toString();
}

// Concrete products. The shared_ptr factory is shared with the creating store and
// kept for prepare(); explicit prevents accidental implicit conversion from a factory.
class CheesePizza2 : public Pizza2 {
public:
    explicit CheesePizza2(std::shared_ptr<IngredientFactory> f) : ingredientFactory(std::move(f)) {}
    void prepare() override {
        std::cout << "Preparing " << name << "\n";
        dough = ingredientFactory->createDough();
        std::cout << "  dough: " << dough->toString() << "\n";
        sauce = ingredientFactory->createSauce();
        std::cout << "  sauce: " << sauce->toString() << "\n";
        cheese = ingredientFactory->createCheese();
        std::cout << "  cheese: " << cheese->toString() << "\n";
    }

private:
    std::shared_ptr<IngredientFactory> ingredientFactory;
};

class ClamPizza2 : public Pizza2 {
public:
    explicit ClamPizza2(std::shared_ptr<IngredientFactory> f) : ingredientFactory(std::move(f)) {}
    void prepare() override {
        std::cout << "Preparing " << name << "\n";
        dough = ingredientFactory->createDough();
        std::cout << "  dough: " << dough->toString() << "\n";
        sauce = ingredientFactory->createSauce();
        std::cout << "  sauce: " << sauce->toString() << "\n";
        cheese = ingredientFactory->createCheese();
        std::cout << "  cheese: " << cheese->toString() << "\n";
        clams = ingredientFactory->createClam();
        std::cout << "  clams: " << clams->toString() << "\n";
    }

private:
    std::shared_ptr<IngredientFactory> ingredientFactory;
};

class VeggiePizza2 : public Pizza2 {
public:
    explicit VeggiePizza2(std::shared_ptr<IngredientFactory> f) : ingredientFactory(std::move(f)) {}
    void prepare() override {
        std::cout << "Preparing " << name << "\n";
        dough = ingredientFactory->createDough();
        std::cout << "  dough: " << dough->toString() << "\n";
        sauce = ingredientFactory->createSauce();
        std::cout << "  sauce: " << sauce->toString() << "\n";
        cheese = ingredientFactory->createCheese();
        std::cout << "  cheese: " << cheese->toString() << "\n";
        veggies = ingredientFactory->createVeggies();
        std::cout << "  veggies: " << veggiesToString() << "\n";
    }

private:
    std::shared_ptr<IngredientFactory> ingredientFactory;
};

class PepperoniPizza2 : public Pizza2 {
public:
    explicit PepperoniPizza2(std::shared_ptr<IngredientFactory> f) : ingredientFactory(std::move(f)) {}
    void prepare() override {
        std::cout << "Preparing " << name << "\n";
        dough = ingredientFactory->createDough();
        std::cout << "  dough: " << dough->toString() << "\n";
        sauce = ingredientFactory->createSauce();
        std::cout << "  sauce: " << sauce->toString() << "\n";
        cheese = ingredientFactory->createCheese();
        std::cout << "  cheese: " << cheese->toString() << "\n";
        veggies = ingredientFactory->createVeggies();
        std::cout << "  veggies: " << veggiesToString() << "\n";
        pepperoni = ingredientFactory->createPepperoni();
        std::cout << "  pepperoni: " << pepperoni->toString() << "\n";
    }

private:
    std::shared_ptr<IngredientFactory> ingredientFactory;
};
