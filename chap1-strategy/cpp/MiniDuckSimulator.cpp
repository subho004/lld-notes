// Entry point (client): exercises the Strategy pattern with ducks and a duck call.
#include <iostream>
#include <memory>

#include "Duck.h"
#include "DuckCall.h"
#include "FlyBehavior.h"

int main() {
    // Held by base pointer: client code only knows the Duck interface.
    std::cout << "Mallard Duck\n";
    std::unique_ptr<Duck> mallard = std::make_unique<MallardDuck>();
    mallard->performFly();
    mallard->performQuack();

    std::cout << "Model Duck\n";
    std::unique_ptr<Duck> model = std::make_unique<ModelDuck>();
    model->performFly();
    // Runtime swap of the strategy: the model duck now flies with a rocket.
    model->setFlyBehavior(std::make_unique<FlyRocketPowered>());
    model->performFly();

    std::cout << "Duck Call!\n";
    DuckCall duckCall;
    duckCall.performQuack();
    return 0;
}
