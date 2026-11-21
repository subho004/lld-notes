"""Adapter pattern: Goose (the Adaptee) and GooseAdapter."""

from __future__ import annotations

from observable import Observable
from quackable import Observer, Quackable


class Goose:
    """Adaptee: has honk() instead of quack()."""

    def honk(self) -> None:
        print("Honk")


class GooseAdapter(Quackable):
    """Adapter: makes a Goose look like a Quackable."""

    def __init__(self, goose: Goose) -> None:
        self.goose = goose
        self.observable = Observable(self)

    def quack(self) -> None:
        self.goose.honk()  # translate quack() into the adaptee's honk()
        self.notify_observers()

    def register_observer(self, observer: Observer) -> None:
        self.observable.register_observer(observer)

    def notify_observers(self) -> None:
        self.observable.notify_observers()

    def __str__(self) -> str:
        return "Goose pretending to be a Duck"
