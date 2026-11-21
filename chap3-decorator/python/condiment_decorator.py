"""Decorator side of the pattern: abstract CondimentDecorator and Mocha, Soy, Whip."""

from abc import abstractmethod

from beverage import Beverage
from size import Size


class CondimentDecorator(Beverage):
    """Abstract Decorator: is-a Beverage and has-a Beverage, so decorators can be stacked."""

    def __init__(self, beverage: Beverage) -> None:
        super().__init__()
        # The wrapped component; all decorated behavior delegates inward to it.
        self.beverage = beverage

    # Re-declared abstract to force each decorator to extend the wrapped description.
    @abstractmethod
    def get_description(self) -> str: ...

    def has_milk(self) -> bool:
        return False

    def has_soy(self) -> bool:
        return False

    def has_mocha(self) -> bool:
        return False

    def has_whip(self) -> bool:
        return False

    # Forward size inward so the innermost drink's size is seen by every decorator.
    def get_size(self) -> Size:
        return self.beverage.get_size()


class Mocha(CondimentDecorator):
    """Concrete Decorator: adds Mocha."""

    def get_description(self) -> str:
        return self.beverage.get_description() + ", Mocha"

    def cost(self) -> float:
        # Delegate inward, then add this decorator's own price.
        return 0.20 + self.beverage.cost()


class Soy(CondimentDecorator):
    """Concrete Decorator: adds Soy, priced by the wrapped drink's size."""

    def get_description(self) -> str:
        return self.beverage.get_description() + ", Soy"

    def cost(self) -> float:
        cost = self.beverage.cost()
        size = self.beverage.get_size()
        if size == Size.TALL:
            cost += 0.10
        elif size == Size.GRANDE:
            cost += 0.15
        elif size == Size.VENTI:
            cost += 0.20
        return cost


class Whip(CondimentDecorator):
    """Concrete Decorator: adds Whip."""

    def get_description(self) -> str:
        return self.beverage.get_description() + ", Whip"

    def cost(self) -> float:
        return 0.10 + self.beverage.cost()
