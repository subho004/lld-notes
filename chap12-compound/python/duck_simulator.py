"""Client / driver for the duck simulator, wiring together all the compound patterns."""

from __future__ import annotations

from duck_factories import AbstractDuckFactory, CountingDuckFactory
from flock import Flock
from goose import Goose, GooseAdapter
from quack_counter import QuackCounter
from quackable import Quackable
from quackologist import Quackologist


class DuckSimulator:
    """Client: builds ducks from a factory and drives them through the Quackable interface."""

    def simulate(self, duck_factory: AbstractDuckFactory) -> None:
        redhead_duck = duck_factory.create_redhead_duck()
        duck_call = duck_factory.create_duck_call()
        rubber_duck = duck_factory.create_rubber_duck()
        # Adapter: a Goose is made usable wherever a Quackable is expected.
        goose_duck = GooseAdapter(Goose())

        # Composite: flocks hold ducks (and other flocks) and are quacked as one.
        flock_of_ducks = Flock()
        flock_of_ducks.add(redhead_duck)
        flock_of_ducks.add(duck_call)
        flock_of_ducks.add(rubber_duck)
        flock_of_ducks.add(goose_duck)

        flock_of_mallards = Flock()
        for _ in range(4):
            flock_of_mallards.add(duck_factory.create_mallard_duck())
        flock_of_ducks.add(flock_of_mallards)

        print("\nDuck Simulator: With Observer")

        # Observer: registering on the flock registers on every duck inside it.
        quackologist = Quackologist()
        flock_of_ducks.register_observer(quackologist)

        self.simulate_duck(flock_of_ducks)

        # The counter is a class-level total shared by all QuackCounter decorators.
        print(f"\nThe ducks quacked {QuackCounter.get_quacks()} times")

    def simulate_duck(self, duck: Quackable) -> None:
        duck.quack()


def main() -> None:
    # Swap in DuckFactory here to run the same simulation without counting.
    simulator = DuckSimulator()
    duck_factory = CountingDuckFactory()
    simulator.simulate(duck_factory)


if __name__ == "__main__":
    main()
