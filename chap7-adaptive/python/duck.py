"""Target interface Duck (what clients expect) and its concrete MallardDuck."""
from abc import ABC, abstractmethod


class Duck(ABC):
    """Target interface for the Turkey->Duck adapter; ABC stands in for a Java interface."""

    @abstractmethod
    def quack(self) -> None: ...

    @abstractmethod
    def fly(self) -> None: ...


class MallardDuck(Duck):
    """Concrete Duck (also the adaptee wrapped by DuckAdapter)."""

    def quack(self) -> None:
        print("Quack")

    def fly(self) -> None:
        print("I'm flying")
