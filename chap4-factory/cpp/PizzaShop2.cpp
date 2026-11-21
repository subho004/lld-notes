// Entry point: Abstract Factory demo. The same order yields different ingredients per
// store; `*pizza` is printed through Pizza2's operator<<.
#include <iostream>
#include <memory>

#include "PizzaStore2.h"

int main() {
    std::unique_ptr<PizzaStore2> nyStore = std::make_unique<NYPizzaStore2>();
    std::unique_ptr<PizzaStore2> chicagoStore = std::make_unique<ChicagoPizzaStore2>();

    std::cout << "=== Same pizza type, different ingredient factories ===\n\n";

    auto pizza = nyStore->orderPizza("cheese");
    std::cout << "Ethan ordered a " << pizza->getName() << "\n";
    std::cout << *pizza << "\n";

    pizza = chicagoStore->orderPizza("cheese");
    std::cout << "Joel ordered a " << pizza->getName() << "\n";
    std::cout << *pizza << "\n";

    std::cout << "=== Full factory usage (veggies, pepperoni, clams) ===\n\n";

    pizza = nyStore->orderPizza("veggie");
    std::cout << "Ethan ordered a " << pizza->getName() << "\n";
    std::cout << *pizza << "\n";

    pizza = chicagoStore->orderPizza("pepperoni");
    std::cout << "Joel ordered a " << pizza->getName() << "\n";
    std::cout << *pizza << "\n";

    pizza = nyStore->orderPizza("clam");
    std::cout << "Ethan ordered a " << pizza->getName() << "\n";
    std::cout << *pizza << "\n";

    pizza = chicagoStore->orderPizza("clam");
    std::cout << "Joel ordered a " << pizza->getName() << "\n";
    std::cout << *pizza << "\n";
    return 0;
}
