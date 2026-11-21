// Client / driver for the duck simulator, combining Adapter, Decorator,
// Abstract Factory, Composite and Observer.
#include <iostream>
#include <memory>

#include "AbstractDuckFactory.h"
#include "CountingDuckFactory.h"
#include "Flock.h"
#include "Goose.h"
#include "GooseAdapter.h"
#include "QuackCounter.h"
#include "Quackable.h"
#include "Quackologist.h"

// Works only against the factory and Quackable interfaces.
class DuckSimulator {
public:
    void simulate(AbstractDuckFactory& duckFactory) {
        auto redheadDuck = duckFactory.createRedheadDuck();
        auto duckCall = duckFactory.createDuckCall();
        auto rubberDuck = duckFactory.createRubberDuck();
        // Adapter: a Goose is usable wherever a Quackable is expected.
        std::shared_ptr<Quackable> gooseDuck = std::make_shared<GooseAdapter>(std::make_shared<Goose>());

        // Composite: flocks hold ducks and other flocks, and quack as one.
        auto flockOfDucks = std::make_shared<Flock>();
        flockOfDucks->add(redheadDuck);
        flockOfDucks->add(duckCall);
        flockOfDucks->add(rubberDuck);
        flockOfDucks->add(gooseDuck);

        auto flockOfMallards = std::make_shared<Flock>();
        for (int i = 0; i < 4; i++) {
            flockOfMallards->add(duckFactory.createMallardDuck());
        }
        flockOfDucks->add(flockOfMallards);

        std::cout << "\nDuck Simulator: With Observer" << std::endl;

        // Observer: the caller owns the quackologist; ducks only hold weak_ptrs to it.
        auto quackologist = std::make_shared<Quackologist>();
        flockOfDucks->registerObserver(quackologist);

        simulate(*flockOfDucks);

        std::cout << "\nThe ducks quacked " << QuackCounter::getQuacks() << " times" << std::endl;
    }

    void simulate(Quackable& duck) { duck.quack(); }
};

int main() {
    DuckSimulator simulator;
    // unique_ptr: main is the sole owner; swap in DuckFactory to disable counting.
    std::unique_ptr<AbstractDuckFactory> duckFactory = std::make_unique<CountingDuckFactory>();
    simulator.simulate(*duckFactory);
    return 0;
}
