"""Observer-pattern interfaces: Observer, DisplayElement and Subject.

Python has no `interface`, so abstract base classes (abc.ABC) play that role.
"""
from abc import ABC, abstractmethod


class Observer(ABC):
    # Observer role: the subject calls update() whenever its state changes.
    @abstractmethod
    def update(self) -> None:
        ...


class DisplayElement(ABC):
    # Separate interface so rendering is independent of observing.
    @abstractmethod
    def display(self) -> None:
        ...


class Subject(ABC):
    # Subject role: manages the observer list and notifies it on changes.
    @abstractmethod
    def register_observer(self, o: Observer) -> None:
        ...

    @abstractmethod
    def remove_observer(self, o: Observer) -> None:
        ...

    @abstractmethod
    def notify_observers(self) -> None:
        ...
