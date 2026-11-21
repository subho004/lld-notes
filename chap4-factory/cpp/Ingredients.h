#pragma once
// Ingredient interfaces and concrete ingredients (Abstract Factory products).
// The Java interfaces are empty and rely on Object.toString(); in C++ the
// interfaces declare toString() so ingredients can be printed polymorphically.
#include <string>

// Product interfaces of the Abstract Factory. Virtual destructors let
// unique_ptr<Dough> etc. delete the concrete ingredient correctly.
class Dough {
public:
    virtual ~Dough() = default;
    virtual std::string toString() const = 0;
};

class Sauce {
public:
    virtual ~Sauce() = default;
    virtual std::string toString() const = 0;
};

class Cheese {
public:
    virtual ~Cheese() = default;
    virtual std::string toString() const = 0;
};

class Veggies {
public:
    virtual ~Veggies() = default;
    virtual std::string toString() const = 0;
};

class Pepperoni {
public:
    virtual ~Pepperoni() = default;
    virtual std::string toString() const = 0;
};

class Clams {
public:
    virtual ~Clams() = default;
    virtual std::string toString() const = 0;
};

// Macro stamps out one concrete product class per ingredient (undefined below).
#define INGREDIENT(Cls, Base, Text)                                  \
    class Cls : public Base {                                        \
    public:                                                          \
        std::string toString() const override { return Text; }       \
    };

INGREDIENT(ThickCrustDough, Dough, "Thick Crust Dough")
INGREDIENT(ThinCrustDough, Dough, "Thin Crust Dough")
INGREDIENT(MarinaraSauce, Sauce, "Marinara Sauce")
INGREDIENT(PlumTomatoSauce, Sauce, "Plum Tomato Sauce")
INGREDIENT(MozzarellaCheese, Cheese, "Mozzarella Cheese")
INGREDIENT(ReggianoCheese, Cheese, "Reggiano Cheese")
INGREDIENT(BlackOlives, Veggies, "Black Olives")
INGREDIENT(Eggplant, Veggies, "Eggplant")
INGREDIENT(Garlic, Veggies, "Garlic")
INGREDIENT(Mushroom, Veggies, "Mushroom")
INGREDIENT(Onion, Veggies, "Onion")
INGREDIENT(RedPepper, Veggies, "Red Pepper")
INGREDIENT(Spinach, Veggies, "Spinach")
INGREDIENT(SlicedPepperoni, Pepperoni, "Sliced Pepperoni")
INGREDIENT(FreshClams, Clams, "Fresh Clams")
INGREDIENT(FrozenClams, Clams, "Frozen Clams")

#undef INGREDIENT
