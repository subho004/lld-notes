"""Turkey interface and WildTurkey: the adaptee wrapped by TurkeyAdapter."""
from abc import ABC, abstractmethod


class Turkey(ABC):
    """Interface incompatible with Duck (gobble instead of quack); ABC mirrors a Java interface."""

    @abstractmethod
    def gobble(self) -> None: ...

    @abstractmethod
    def fly(self) -> None: ...


class WildTurkey(Turkey):
    """Concrete Turkey (the adaptee)."""

    def gobble(self) -> None:
        print("Gobble gobble")

    def fly(self) -> None:
        print("I'm flying a short distance")
