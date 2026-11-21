"""Quack strategy family: QuackBehavior (Strategy interface) and its concrete strategies.

Quack, Squeak and MuteQuack are interchangeable at runtime.
"""
from abc import ABC, abstractmethod


class QuackBehavior(ABC):
    """Strategy interface: one swappable quacking algorithm."""

    @abstractmethod
    def quack(self) -> None: ...


# Concrete strategies: each encapsulates one way of quacking.
class Quack(QuackBehavior):
    def quack(self) -> None:
        print("Quack")


class Squeak(QuackBehavior):
    def quack(self) -> None:
        print("Squeak")


class MuteQuack(QuackBehavior):
    def quack(self) -> None:
        print("<< Silence >>")
