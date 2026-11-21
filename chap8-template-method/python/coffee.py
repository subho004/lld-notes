"""Concrete class: Coffee supplies the brew and condiment steps of the template."""
from caffiene_beverage import CaffieneBeverage


class Coffee(CaffieneBeverage):
    """Concrete subclass: fills in the abstract steps only; the algorithm order is inherited."""

    def brew(self) -> None:
        print("Brewing coffee")

    def add_condiments(self) -> None:
        print("Adding sugar and milk")


def main() -> None:
    coffee = Coffee()
    coffee.prepare_recipe()


if __name__ == "__main__":
    main()
