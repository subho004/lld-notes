"""Abstract base (Template Method) for Coffee and Tea; the name keeps the Java typo."""
from abc import ABC, abstractmethod
from typing import final


class CaffieneBeverage(ABC):
    """Template Method: prepare_recipe() fixes the algorithm skeleton."""

    # @final is only enforced by type checkers; Java uses a real `final`.
    @final
    def prepare_recipe(self) -> None:
        self.boil_water()
        self.brew()
        self.pour_in_cup()
        self.add_condiments()

    # Steps the subclasses must supply (ABC blocks instantiation until they do).
    @abstractmethod
    def brew(self) -> None: ...

    @abstractmethod
    def add_condiments(self) -> None: ...

    # Steps shared by every beverage live in the base class.
    def boil_water(self) -> None:
        print("Boiling water")

    def pour_in_cup(self) -> None:
        print("Pouring into cup")
