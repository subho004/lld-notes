"""Singleton (classic, lazy, lock-protected) and NewSingleton (__new__ based variant)."""
import threading
from typing import Optional


class Singleton:
    """Classic lazy Singleton; the lock makes get_instance() thread-safe
    (like Java's synchronized getInstance())."""

    # Holds the one instance; Python has no private constructor, so use is by convention.
    _unique_instance: Optional["Singleton"] = None
    _lock = threading.Lock()

    def __init__(self) -> None:
        pass

    @classmethod
    def get_instance(cls) -> "Singleton":
        with cls._lock:
            if cls._unique_instance is None:
                cls._unique_instance = cls()
            return cls._unique_instance


class NewSingleton:
    """Pythonic variant: __new__ always hands back the same object."""

    _instance: Optional["NewSingleton"] = None
    _lock = threading.Lock()

    # Constructing NewSingleton() any number of times yields the same object.
    def __new__(cls) -> "NewSingleton":
        if cls._instance is None:
            with cls._lock:
                if cls._instance is None:
                    cls._instance = super().__new__(cls)
        return cls._instance
