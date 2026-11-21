"""Decorator pattern: QuackCounter."""

from __future__ import annotations

from quackable import Observer, Quackable


class QuackCounter(Quackable):
    """Decorator: counts every quack of the wrapped Quackable."""

    number_of_quacks = 0  # class attribute, shared by all counters (Java static)

    def __init__(self, duck: Quackable) -> None:
        self.duck = duck

    def quack(self) -> None:
        self.duck.quack()  # delegate first, then add the counting behavior
        QuackCounter.number_of_quacks += 1

    @staticmethod
    def get_quacks() -> int:
        return QuackCounter.number_of_quacks

    def register_observer(self, observer: Observer) -> None:
        # Pure delegation: observers end up on the wrapped duck.
        self.duck.register_observer(observer)

    def notify_observers(self) -> None:
        self.duck.notify_observers()
