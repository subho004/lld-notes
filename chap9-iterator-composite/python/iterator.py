"""Iterator pattern: the Iterator interface and one concrete iterator per menu.

Each iterator hides how its menu stores items (list, fixed array, dict).
"""
from abc import ABC, abstractmethod
from typing import Dict, Iterator as PyIterator, List, Optional

from java_hash_order import java_hashmap_order
from menu_item import MenuItem


class Iterator(ABC):
    """Iterator interface (the pattern's Iterator role). Book-style iterator (hasNext/next). Also implements Python's native
    iterator protocol, so any of these can be used directly in a for loop."""

    @abstractmethod
    def has_next(self) -> bool: ...

    @abstractmethod
    def next(self) -> MenuItem: ...

    # --- native Python iterator protocol, built on has_next()/next() ---
    def __iter__(self) -> "Iterator":
        return self

    def __next__(self) -> MenuItem:
        if not self.has_next():
            raise StopIteration
        return self.next()


class PancakeHouseIterator(Iterator):
    """Concrete Iterator over a plain list (PancakeHouseMenu)."""

    def __init__(self, items: List[MenuItem]) -> None:
        self.items = items
        self.position = 0

    def next(self) -> MenuItem:
        menu_item = self.items[self.position]
        self.position = self.position + 1
        return menu_item

    def has_next(self) -> bool:
        return self.position < len(self.items)


class DinerMenuIterator(Iterator):
    """Concrete Iterator over a fixed-size list whose unused slots are None."""

    def __init__(self, items: List[Optional[MenuItem]]) -> None:
        self.items = items
        self.position = 0

    def next(self) -> MenuItem:
        item = self.items[self.position]
        self.position += 1
        assert item is not None
        return item

    def has_next(self) -> bool:
        # None marks the first unused slot, i.e. the end of the real items.
        return self.position < len(self.items) and self.items[self.position] is not None

    def remove(self) -> None:
        raise NotImplementedError("You shouldn't be trying to remove menu items")


class AlternatingDinerMenuIterator(Iterator):
    """Concrete Iterator that visits every other slot (step of 2). Unused by the demos."""

    DAY_OF_WEEK = 7  # java.util.Calendar.DAY_OF_WEEK is the constant 7

    def __init__(self, items: List[Optional[MenuItem]]) -> None:
        self.items = items
        self.position = self.DAY_OF_WEEK % 2

    def next(self) -> MenuItem:
        menu_item = self.items[self.position]
        self.position = self.position + 2
        assert menu_item is not None
        return menu_item

    def has_next(self) -> bool:
        return not (self.position >= len(self.items) or self.items[self.position] is None)

    def remove(self) -> None:
        raise NotImplementedError("Alternating Diner Menu Iterator does not support remove()")


# Java ships a second, identical copy (AlternatingDinerMenuIterator2); kept for parity.
class AlternatingDinerMenuIterator2(AlternatingDinerMenuIterator):
    pass


class CafeMenuIterator(Iterator):
    """Concrete Iterator over a dict, wrapping Python's native iterator (Java wraps a HashMap iterator)."""

    def __init__(self, items: Dict[str, MenuItem]) -> None:
        self.items = items
        # Java iterates HashMap.values(); reproduce that order.
        ordered = java_hashmap_order(list(items.keys()), list(items.values()))
        self.iterator: PyIterator[MenuItem] = iter(ordered)
        # One-item lookahead so has_next() can be answered without consuming.
        self._peek: Optional[MenuItem] = next(self.iterator, None)

    def next(self) -> MenuItem:
        if self._peek is None:
            raise StopIteration
        current = self._peek
        self._peek = next(self.iterator, None)
        return current

    def has_next(self) -> bool:
        return self._peek is not None
