// Entry point: demonstrates the dependent store. Dereferences results without a null
// check, which is safe here because both orders are valid types.
#include <iostream>

#include "DependentPizzaStore.h"

int main() {
    DependentPizzaStore store;

    auto nyPizza = store.createPizza("NY", "cheese");
    nyPizza->prepare();
    std::cout << "Ordered: " << nyPizza->getName() << "\n\n";

    auto chicagoPizza = store.createPizza("Chicago", "pepperoni");
    chicagoPizza->prepare();
    std::cout << "Ordered: " << chicagoPizza->getName() << "\n";
    return 0;
}
