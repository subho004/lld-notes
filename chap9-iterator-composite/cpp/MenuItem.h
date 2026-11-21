#pragma once
// MenuItem: plain element stored by the menus. Header-only; shared via shared_ptr.
#include <string>
#include <utility>

class MenuItem {
    std::string name;
    std::string description;
    bool vegetarian;
    double price;

public:
    // By-value strings plus std::move avoids a copy when callers pass temporaries.
    MenuItem(std::string name, std::string description, bool vegetarian, double price)
        : name(std::move(name)), description(std::move(description)), vegetarian(vegetarian), price(price) {}

    std::string getName() const { return name; }
    std::string getDescription() const { return description; }
    double getPrice() const { return price; }
    bool isVegetarian() const { return vegetarian; }
};
