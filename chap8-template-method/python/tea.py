"""Concrete class: Tea supplies the brew and condiment steps of the template."""
from caffiene_beverage import CaffieneBeverage


class Tea(CaffieneBeverage):
    """Concrete subclass: fills in the abstract steps only; the algorithm order is inherited."""

    def brew(self) -> None:
        print("Steeping tea bag")

    def add_condiments(self) -> None:
        print("Adding lemon")


def main() -> None:
    tea = Tea()
    tea.prepare_recipe()


if __name__ == "__main__":
    main()
