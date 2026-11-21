#pragma once
// Pizza (string-based version) and all concrete pizzas.
#include <iostream>
#include <string>
#include <vector>

// Product base. Methods are virtual so subclasses (e.g. Chicago) can override cut();
// the virtual destructor is required because pizzas are deleted through unique_ptr<Pizza>.
class Pizza {
public:
    virtual ~Pizza() = default;

    virtual void prepare() {
        std::cout << "Preparing " << name << "\n";
        std::cout << "Tossing dough...\n";
        std::cout << "Adding sauce...\n";
        std::cout << "Adding toppings: \n";
        for (const auto& topping : toppings) {
            std::cout << "    " << topping << "\n";
        }
    }
    virtual void bake() { std::cout << "Bake for 25 minutes at 350\n"; }
    virtual void cut() { std::cout << "Cutting the pizza into diagonal slices\n"; }
    virtual void box() { std::cout << "Place pizza in official PizzaStore box\n"; }
    std::string getName() const { return name; }

protected:
    std::string name;
    std::string dough;
    std::string sauce;
    std::vector<std::string> toppings;
};

// Concrete products configure the inherited protected fields in their constructors.
// ---- Simple factory pizzas ----
class CheesePizza : public Pizza {
public:
    CheesePizza() {
        name = "Cheese Pizza";
        dough = "Regular Crust";
        sauce = "Marinara Pizza Sauce";
        toppings = {"Fresh Mozzarella", "Parmesan"};
    }
};

class ClamPizza : public Pizza {
public:
    ClamPizza() {
        name = "Clam Pizza";
        dough = "Thin Crust";
        sauce = "White Garlic Sauce";
        toppings = {"Clams", "Grated parmesan cheese"};
    }
};

class PepperoniPizza : public Pizza {
public:
    PepperoniPizza() {
        name = "Pepperoni Pizza";
        dough = "Regular Crust";
        sauce = "Marinara Pizza Sauce";
        toppings = {"Sliced Pepperoni", "Sliced Onion", "Grated parmesan cheese"};
    }
};

class VeggiePizza : public Pizza {
public:
    VeggiePizza() {
        name = "Veggie Pizza";
        dough = "Crust";
        sauce = "Marinara Sauce";
        toppings = {"Shredded mozzarella", "Diced onion", "Sliced mushrooms",
                    "Sliced red pepper", "Sliced black olives"};
    }
};

// ---- New York style ----
class NYStyleCheesePizza : public Pizza {
public:
    NYStyleCheesePizza() {
        name = "NY Style Sauce and Cheese Pizza";
        dough = "Thin Crust Dough";
        sauce = "Marinara Sauce";
        toppings = {"Grated Reggiano Cheese"};
    }
};

class NYStyleClamPizza : public Pizza {
public:
    NYStyleClamPizza() {
        name = "NY Style Clam Pizza";
        dough = "Thin Crust Dough";
        sauce = "Marinara Sauce";
        toppings = {"Grated Reggiano Cheese", "Fresh Clams from Long Island Sound"};
    }
};

class NYStylePepperoniPizza : public Pizza {
public:
    NYStylePepperoniPizza() {
        name = "NY Style Pepperoni Pizza";
        dough = "Thin Crust Dough";
        sauce = "Marinara Sauce";
        toppings = {"Grated Reggiano Cheese", "Sliced Pepperoni", "Garlic",
                    "Onion", "Mushrooms", "Red Pepper"};
    }
};

class NYStyleVeggiePizza : public Pizza {
public:
    NYStyleVeggiePizza() {
        name = "NY Style Veggie Pizza";
        dough = "Thin Crust Dough";
        sauce = "Marinara Sauce";
        toppings = {"Grated Reggiano Cheese", "Garlic", "Onion", "Mushrooms",
                    "Red Pepper"};
    }
};

// ---- Chicago style ----
class ChicagoStyleCheesePizza : public Pizza {
public:
    ChicagoStyleCheesePizza() {
        name = "Chicago Style Deep Dish Cheese Pizza";
        dough = "Extra Thick Crust Dough";
        sauce = "Plum Tomato Sauce";
        toppings = {"Shredded Mozzarella Cheese"};
    }
    // Chicago pizzas override cut() to use square slices.
    void cut() override { std::cout << "Cutting the pizza into square slices\n"; }
};

class ChicagoStyleClamPizza : public Pizza {
public:
    ChicagoStyleClamPizza() {
        name = "Chicago Style Deep Dish Clam Pizza";
        dough = "Extra Thick Crust Dough";
        sauce = "Plum Tomato Sauce";
        toppings = {"Shredded Mozzarella Cheese", "Fresh Clams"};
    }
    void cut() override { std::cout << "Cutting the pizza into square slices\n"; }
};

class ChicagoStylePepperoniPizza : public Pizza {
public:
    ChicagoStylePepperoniPizza() {
        name = "Chicago Style Deep Dish Pepperoni Pizza";
        dough = "Extra Thick Crust Dough";
        sauce = "Plum Tomato Sauce";
        toppings = {"Shredded Mozzarella Cheese", "Sliced Pepperoni"};
    }
    void cut() override { std::cout << "Cutting the pizza into square slices\n"; }
};

// ---- California style ----
class CaliforniaStyleCheesePizza : public Pizza {
public:
    CaliforniaStyleCheesePizza() {
        name = "California Style Cheese Pizza";
        dough = "Very Thin Crust Dough";
        sauce = "Bruschetta Sauce";
        toppings = {"Goat Cheese", "Fresh Mozzarella"};
    }
};

class CaliforniaStyleClamPizza : public Pizza {
public:
    CaliforniaStyleClamPizza() {
        name = "California Style Clam Pizza";
        dough = "Very Thin Crust Dough";
        sauce = "White Wine Sauce";
        toppings = {"Fresh Clams", "Garlic", "Lemon Zest"};
    }
};

class CaliforniaStylePepperoniPizza : public Pizza {
public:
    CaliforniaStylePepperoniPizza() {
        name = "California Style Pepperoni Pizza";
        dough = "Very Thin Crust Dough";
        sauce = "Bruschetta Sauce";
        toppings = {"Goat Cheese", "Artisan Pepperoni", "Arugula"};
    }
};

class CaliforniaStyleVeggiePizza : public Pizza {
public:
    CaliforniaStyleVeggiePizza() {
        name = "California Style Veggie Pizza";
        dough = "Very Thin Crust Dough";
        sauce = "Pesto Sauce";
        toppings = {"Goat Cheese", "Avocado", "Sundried Tomato", "Spinach"};
    }
};
