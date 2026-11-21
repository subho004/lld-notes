"""Composite pattern: Flock."""

from __future__ import annotations

from quackable import Observer, Quackable


class Flock(Quackable):
    """Composite: a group of Quackables that is itself a Quackable."""

    def __init__(self) -> None:
        self.ducks: list[Quackable] = []

    def add(self, duck: Quackable) -> None:
        self.ducks.append(duck)

    def quack(self) -> None:
        # Composite mechanic: delegate to every child, which may itself be a Flock.
        for duck in self.ducks:
            duck.quack()

    def register_observer(self, observer: Observer) -> None:
        # Observers are registered on the leaf ducks, not on the flock itself.
        for duck in self.ducks:
            duck.register_observer(observer)

    def notify_observers(self) -> None:
        # Intentionally empty: each duck notifies its own observers when it quacks.
        pass
