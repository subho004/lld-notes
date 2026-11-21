// Client: only calls Car; the printed "bad" examples are text, not real calls.
#include <iostream>
#include <memory>

#include "Car.h"

int main() {
    // Parts are handed over by unique_ptr, so Car becomes their only owner.
    Car car(std::make_unique<Engine>(), std::make_unique<Wheels>(), std::make_unique<Doors>());

    std::cout << "--- Good: client only talks to Car (Law of Demeter) ---\n";
    car.start();
    car.drive();
    car.park();
    car.refuel();

    std::cout << "\n--- Bad: reaching into Car's parts from outside ---\n";
    std::cout << "(This would violate the Law of Demeter)\n";
    std::cout << "car.getEngine().start();  // don't do this\n";
    std::cout << "car.getDoors().unlock();  // don't do this\n";
    std::cout << "Instead, call car.start() and let Car coordinate its components.\n";
    return 0;
}
