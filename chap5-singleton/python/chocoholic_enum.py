"""ChocoholicEnum: second enum-style Singleton (mirrors the Java enum used by Chocoholic)."""
from enum import Enum


class ChocoholicEnum(Enum):
    # The only member; Enum guarantees it is created once.
    INSTANCE = 1

    def eat_chocolate(self) -> None:
        print("Eating chocolate")
