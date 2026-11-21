"""Fly strategy family: FlyBehavior (Strategy interface) and its concrete strategies.

FlyWithWings, FlyNoWay and FlyRocketPowered are interchangeable at runtime.
ABC + @abstractmethod plays the role of Java's interface.
"""
from abc import ABC, abstractmethod


class FlyBehavior(ABC):
    """Strategy interface: one swappable flying algorithm."""

    @abstractmethod
    def fly(self) -> None: ...


# Concrete strategies: each encapsulates one flying behavior.
class FlyWithWings(FlyBehavior):
    def fly(self) -> None:
        print("I'm flying!!")


class FlyNoWay(FlyBehavior):
    def fly(self) -> None:
        print("I can't fly")


class FlyRocketPowered(FlyBehavior):
    def fly(self) -> None:
        print("I'm flying with a rocket!")
