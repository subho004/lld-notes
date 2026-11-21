// Entry point: Factory Method demo. Stores are held by the abstract PizzaStore type;
// reassigning `pizza` destroys the previous pizza (unique_ptr ownership).
#include <iostream>
#include <memory>

#include "PizzaStore.h"

int main() {
    std::unique_ptr<PizzaStore> nyStore = std::make_unique<NYStylePizzaStore>();
    std::unique_ptr<PizzaStore> californiaStore = std::make_unique<CaliforniaStylePizzaStore>();

    auto pizza = nyStore->orderPizza("cheese");
    std::cout << "Ethan ordered a " << pizza->getName() << "\n\n";

    pizza = californiaStore->orderPizza("cheese");
    std::cout << "Joel ordered a " << pizza->getName() << "\n\n";
    return 0;
}
