"""Abstract base (Template Method) whose recipe contains a hook for optional condiments."""
from abc import ABC, abstractmethod
from typing import final


class CaffeineBeverageWithHook(ABC):
    """Template Method with a hook: prepare_recipe() asks the subclass before adding condiments."""

    @final
    def prepare_recipe(self) -> None:
        self.boil_water()
        self.brew()
        self.pour_in_cup()
        # Hollywood Principle: the base class calls the subclass hook, not vice versa.
        if self.customer_wants_condiments():
            self.add_condiments()

    # Abstract steps: every subclass must implement them.
    @abstractmethod
    def brew(self) -> None: ...

    @abstractmethod
    def add_condiments(self) -> None: ...

    def boil_water(self) -> None:
        print("Boiling water")

    def pour_in_cup(self) -> None:
        print("Pouring into cup")

    def customer_wants_condiments(self) -> bool:
        """Hook: subclasses may override."""
        return True
