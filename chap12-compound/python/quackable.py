"""Core interfaces: Observer, QuackObservable (Observer subject) and Quackable.

Java interfaces are modelled as abstract base classes."""

from __future__ import annotations

from abc import ABC, abstractmethod


class Observer(ABC):
    """Observer interface: notified with the duck that quacked."""

    @abstractmethod
    def update(self, duck: "QuackObservable") -> None: ...


class QuackObservable(ABC):
    """Subject interface for observers of quacks."""

    @abstractmethod
    def register_observer(self, observer: Observer) -> None: ...

    @abstractmethod
    def notify_observers(self) -> None: ...


class Quackable(QuackObservable):
    """Common component interface for ducks, adapters, decorators and flocks."""

    @abstractmethod
    def quack(self) -> None: ...
