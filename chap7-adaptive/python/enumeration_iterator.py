"""EnumerationIterator: Adapter exposing an old Enumeration through the Iterator interface."""
from typing import Generic, TypeVar

from java_util import Enumeration, Iterator

T = TypeVar("T")


class EnumerationIterator(Iterator[T], Generic[T]):
    """Adapts an Enumeration to the Iterator interface."""

    def __init__(self, enumeration: Enumeration[T]) -> None:
        self.enumeration = enumeration

    def has_next(self) -> bool:
        return self.enumeration.has_more_elements()

    def next(self) -> T:
        return self.enumeration.next_element()

    def remove(self) -> None:
        # Enumeration cannot remove, so this is unsupported (Java: UnsupportedOperationException).
        raise NotImplementedError("UnsupportedOperationException")
