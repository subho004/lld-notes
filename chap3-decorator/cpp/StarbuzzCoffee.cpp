// Client: builds decorated drinks (Starbuzz Coffee) and prints description and cost.
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>

#include "Beverage.h"
#include "CondimentDecorator.h"

// Shortest decimal string that round-trips (what Java's Double.toString prints
// for these magnitudes); always has a fractional part.
static std::string formatDouble(double v) {
    char buf[64];
    for (int prec = 1; prec <= 17; ++prec) {
        std::snprintf(buf, sizeof buf, "%.*g", prec, v);
        if (std::strtod(buf, nullptr) == v) break;
    }
    std::string s = buf;
    if (s.find_first_of(".e") == std::string::npos) s += ".0";
    return s;
}

static void print(const Beverage& b) {
    std::cout << b.getDescription() << " $" << formatDouble(b.cost()) << "\n";
}

int main() {
    // Each reassignment moves the previous drink into a new decorator, which takes ownership.
    std::unique_ptr<Beverage> beverage = std::make_unique<Expresso>();
    print(*beverage);

    std::unique_ptr<Beverage> beverage2 = std::make_unique<DarkRoast>();
    beverage2 = std::make_unique<Mocha>(std::move(beverage2));
    beverage2 = std::make_unique<Mocha>(std::move(beverage2));
    beverage2 = std::make_unique<Whip>(std::move(beverage2));
    print(*beverage2);

    std::unique_ptr<Beverage> beverage3 = std::make_unique<HouseBlend>();
    beverage3 = std::make_unique<Soy>(std::move(beverage3));
    beverage3 = std::make_unique<Mocha>(std::move(beverage3));
    beverage3 = std::make_unique<Whip>(std::move(beverage3));
    print(*beverage3);

    std::unique_ptr<Beverage> latte = std::make_unique<Expresso>();
    latte = std::make_unique<Mocha>(std::move(latte));
    latte = std::make_unique<Mocha>(std::move(latte));
    latte = std::make_unique<Soy>(std::move(latte));
    latte = std::make_unique<Whip>(std::move(latte));
    print(*latte);

    std::unique_ptr<Beverage> beverage4 = std::make_unique<HouseBlend>();
    beverage4->setSize(Size::GRANDE);
    beverage4 = std::make_unique<Soy>(std::move(beverage4));
    beverage4 = std::make_unique<Mocha>(std::move(beverage4));
    beverage4 = std::make_unique<Whip>(std::move(beverage4));
    print(*beverage4);
    return 0;
}
