"""Concrete Quackables: MallardDuck, RedheadDuck, DuckCall and RubberDuck.

They share one base class, _ObservableDuck, instead of repeating the code four times as the Java does."""

from __future__ import annotations

from observable import Observable
from quackable import Observer, Quackable


class _ObservableDuck(Quackable):
    """Shared plumbing; the Java code repeats this in every duck class.

    Python deviation: subclasses only supply SOUND and NAME. Observer bookkeeping
    is delegated to an Observable helper rather than inherited.
    """

    SOUND = ""
    NAME = ""

    def __init__(self) -> None:
        # Observable needs the duck itself so it can pass it to observers.
        self.observable = Observable(self)

    def quack(self) -> None:
        print(self.SOUND)
        self.notify_observers()  # tell observers after every quack

    def register_observer(self, observer: Observer) -> None:
        self.observable.register_observer(observer)

    def notify_observers(self) -> None:
        self.observable.notify_observers()

    def __str__(self) -> str:
        return self.NAME


class MallardDuck(_ObservableDuck):
    """Concrete Quackable."""

    SOUND = "Quack"
    NAME = "Mallard Duck"


class RedheadDuck(_ObservableDuck):
    """Concrete Quackable."""

    SOUND = "Quack"
    NAME = "Redhead Duck"


class DuckCall(_ObservableDuck):
    """Concrete Quackable."""

    SOUND = "Kwak"
    NAME = "Duck Call"


class RubberDuck(_ObservableDuck):
    """Concrete Quackable."""

    SOUND = "Squeak"
    NAME = "Rubber Duck"
