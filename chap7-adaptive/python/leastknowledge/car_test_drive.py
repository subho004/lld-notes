"""Client: only calls Car; the printed "bad" examples are text, not real calls."""
from car import Car, Doors, Engine, Wheels


def main() -> None:
    car = Car(Engine(), Wheels(), Doors())

    print("--- Good: client only talks to Car (Law of Demeter) ---")
    car.start()
    car.drive()
    car.park()
    car.refuel()

    print("\n--- Bad: reaching into Car's parts from outside ---")
    print("(This would violate the Law of Demeter)")
    print("car.getEngine().start();  // don't do this")
    print("car.getDoors().unlock();  // don't do this")
    print("Instead, call car.start() and let Car coordinate its components.")


if __name__ == "__main__":
    main()
