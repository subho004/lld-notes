"""Concrete Observer: Quackologist."""

from __future__ import annotations

from quackable import Observer, QuackObservable


class Quackologist(Observer):
    """Concrete Observer that reports each quack it is notified about."""

    def update(self, duck: QuackObservable) -> None:
        print(f"Quackologist: {duck} just quacked.")
