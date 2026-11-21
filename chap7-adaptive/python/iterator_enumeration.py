"""IteratorEnumeration: Adapter exposing an Iterator through the Enumeration interface."""
from typing import Generic, TypeVar

from java_util import Enumeration, Iterator

T = TypeVar("T")


class IteratorEnumeration(Enumeration[T], Generic[T]):
    """Adapts an Iterator to the Enumeration interface."""

    def __init__(self, iterator: Iterator[T]) -> None:
        self.iterator = iterator

    def has_more_elements(self) -> bool:
        return self.iterator.has_next()

    def next_element(self) -> T:
        return self.iterator.next()
