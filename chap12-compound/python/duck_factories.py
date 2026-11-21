"""Abstract Factory: AbstractDuckFactory and its two concrete factories.

CountingDuckFactory also applies the Decorator (QuackCounter) while creating ducks."""

from __future__ import annotations

from abc import ABC, abstractmethod

from ducks import DuckCall, MallardDuck, RedheadDuck, RubberDuck
from quack_counter import QuackCounter
from quackable import Quackable


class AbstractDuckFactory(ABC):
    """Abstract Factory: clients create ducks without naming concrete classes."""

    @abstractmethod
    def create_mallard_duck(self) -> Quackable: ...

    @abstractmethod
    def create_redhead_duck(self) -> Quackable: ...

    @abstractmethod
    def create_duck_call(self) -> Quackable: ...

    @abstractmethod
    def create_rubber_duck(self) -> Quackable: ...


class DuckFactory(AbstractDuckFactory):
    """Concrete Factory: plain, undecorated ducks."""

    def create_mallard_duck(self) -> Quackable:
        return MallardDuck()

    def create_redhead_duck(self) -> Quackable:
        return RedheadDuck()

    def create_duck_call(self) -> Quackable:
        return DuckCall()

    def create_rubber_duck(self) -> Quackable:
        return RubberDuck()


class CountingDuckFactory(AbstractDuckFactory):
    """Concrete Factory: wraps every duck in a QuackCounter so quacks are counted."""

    def create_mallard_duck(self) -> Quackable:
        return QuackCounter(MallardDuck())

    def create_redhead_duck(self) -> Quackable:
        return QuackCounter(RedheadDuck())

    def create_duck_call(self) -> Quackable:
        return QuackCounter(DuckCall())

    def create_rubber_duck(self) -> Quackable:
        return QuackCounter(RubberDuck())
