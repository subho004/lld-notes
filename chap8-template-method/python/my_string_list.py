"""AbstractList (template methods) and MyStringList (concrete list), after java.util.AbstractList."""
from abc import ABC, abstractmethod
from typing import Generic, Iterator, List, TypeVar

T = TypeVar("T")


class AbstractList(ABC, Generic[T]):
    """Minimal java.util.AbstractList: subclasses supply get/size (and set);
    iteration and sub_list are template methods built on them."""

    @abstractmethod
    def get(self, index: int) -> T: ...

    @abstractmethod
    def size(self) -> int: ...

    # Optional step: read-only by default, like Java's UnsupportedOperationException.
    def set(self, index: int, element: T) -> T:
        raise NotImplementedError("unsupported operation")

    # Template method: iteration built on the abstract get()/size().
    def __iter__(self) -> Iterator[T]:
        for i in range(self.size()):
            yield self.get(i)

    def __len__(self) -> int:
        return self.size()

    def sub_list(self, from_index: int, to_index: int) -> "AbstractList[T]":
        if from_index < 0 or to_index > self.size() or from_index > to_index:
            raise IndexError("bad sublist range")
        # Returns a live view (not a copy); writes go through to the parent.
        return _SubList(self, from_index, to_index)


class _SubList(AbstractList[T]):
    """View onto a range of the parent list."""

    def __init__(self, parent: AbstractList[T], start: int, end: int) -> None:
        self._parent = parent
        self._start = start
        self._end = end

    def get(self, index: int) -> T:
        if not 0 <= index < self.size():
            raise IndexError(index)
        return self._parent.get(self._start + index)

    def size(self) -> int:
        return self._end - self._start

    def set(self, index: int, element: T) -> T:
        if not 0 <= index < self.size():
            raise IndexError(index)
        return self._parent.set(self._start + index, element)


class MyStringList(AbstractList[str]):
    """Concrete subclass: supplies only get/size/set; iteration and sub_list come from the base."""

    def __init__(self, strings: List[str]) -> None:
        self._my_list = strings

    def get(self, index: int) -> str:
        return self._my_list[index]

    def size(self) -> int:
        return len(self._my_list)

    def set(self, index: int, element: str) -> str:
        old_string = self._my_list[index]
        self._my_list[index] = element
        return old_string
