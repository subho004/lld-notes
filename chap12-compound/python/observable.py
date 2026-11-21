"""Observer pattern: the Observable helper that ducks delegate to."""

from __future__ import annotations

from quackable import Observer, QuackObservable


class Observable(QuackObservable):
    """Helper that every duck delegates its observer bookkeeping to."""

    def __init__(self, duck: QuackObservable) -> None:
        self.observers: list[Observer] = []
        self.duck = duck  # the real subject, passed to observers on update

    def register_observer(self, observer: Observer) -> None:
        self.observers.append(observer)

    def notify_observers(self) -> None:
        for observer in self.observers:
            observer.update(self.duck)
