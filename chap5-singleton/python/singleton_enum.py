"""SingletonEnum: the Java enum-singleton idiom expressed as a one-member Enum."""
from enum import Enum


class SingletonEnum(Enum):
    """Enum with one member: the language guarantees a single instance."""

    INSTANCE = 1

    def do_something(self) -> None:
        print("SingletonEnum")
