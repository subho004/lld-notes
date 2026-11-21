"""Tiny stand-ins for java.util.Enumeration / Iterator / Vector / ArrayList.

Holds the two incompatible collection interfaces (Enumeration, Iterator) that the
adapters bridge. Python's own iterator protocol differs, so these are re-created.
"""
from abc import ABC, abstractmethod
from typing import Generic, List, TypeVar

T = TypeVar("T")


class Enumeration(ABC, Generic[T]):
    """Legacy interface (Adapter target/adaptee). ABC mirrors the Java interface; Generic is hints only."""

    @abstractmethod
    def has_more_elements(self) -> bool: ...

    @abstractmethod
    def next_element(self) -> T: ...


class Iterator(ABC, Generic[T]):
    """Modern interface (Adapter target/adaptee). remove() is optional, as in Java."""

    @abstractmethod
    def has_next(self) -> bool: ...

    @abstractmethod
    def next(self) -> T: ...

    def remove(self) -> None:
        # Java default method: optional operation, unsupported unless overridden.
        raise NotImplementedError("remove")


class _ListEnumeration(Enumeration[T]):
    """Private Enumeration over a list; what Vector.elements() hands out."""

    def __init__(self, items: List[T]) -> None:
        self._items = items
        self._i = 0

    def has_more_elements(self) -> bool:
        return self._i < len(self._items)

    def next_element(self) -> T:
        item = self._items[self._i]
        self._i += 1
        return item


class _ListIterator(Iterator[T]):
    """Private Iterator over a list; what ArrayList.iterator() hands out."""

    def __init__(self, items: List[T]) -> None:
        self._items = items
        self._i = 0

    def has_next(self) -> bool:
        return self._i < len(self._items)

    def next(self) -> T:
        item = self._items[self._i]
        self._i += 1
        return item


class Vector(Generic[T]):
    """Legacy collection that only offers an Enumeration (via elements())."""

    def __init__(self) -> None:
        self._items: List[T] = []

    def add(self, item: T) -> None:
        self._items.append(item)

    def elements(self) -> Enumeration[T]:
        return _ListEnumeration(self._items)


class ArrayList(Vector[T]):
    """Modern collection; adds iterator() on top of the shared item storage."""

    def iterator(self) -> Iterator[T]:
        return _ListIterator(self._items)
