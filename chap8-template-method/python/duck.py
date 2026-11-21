"""Duck: the element type sorted by list.sort(), the Python counterpart of Comparable<Duck>."""
from functools import total_ordering


@total_ordering
class Duck:
    """Ducks are ordered by weight (Comparable<Duck> -> __lt__/__eq__)."""

    def __init__(self, name: str, weight: int) -> None:
        self.name = name
        self.weight = weight

    def __str__(self) -> str:
        return f"{self.name} weighs {self.weight}"

    # The hook that sort() calls back; total_ordering derives <=, >, >= from it.
    def __lt__(self, other: "Duck") -> bool:
        return self.weight < other.weight

    def __eq__(self, other: object) -> bool:
        return isinstance(other, Duck) and self.weight == other.weight

    # Defining __eq__ would drop hashing anyway; None makes it explicit (Java ducks are not hashed here).
    __hash__ = None  # type: ignore[assignment]
