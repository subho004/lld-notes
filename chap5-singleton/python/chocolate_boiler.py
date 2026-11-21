"""ChocolateBoiler: Singleton with double-checked locking plus synchronized state methods."""
import threading
from typing import Optional


class ChocolateBoiler:
    # Singleton state: the one instance, and a class-level lock guarding its creation.
    _unique_instance: Optional["ChocolateBoiler"] = None
    _class_lock = threading.Lock()

    def __init__(self) -> None:
        # RLock = Java's synchronized: reentrant, so fill() may call is_empty() while holding it.
        self._lock = threading.RLock()
        self._empty = True
        self._boiled = False

    @classmethod
    def get_instance(cls) -> "ChocolateBoiler":
        # double-checked locking, as in the Java version; the unlocked first check
        # is safe under the GIL (no volatile needed).
        if cls._unique_instance is None:
            with cls._class_lock:
                if cls._unique_instance is None:
                    cls._unique_instance = cls()
        return cls._unique_instance

    def fill(self) -> None:
        with self._lock:
            if self.is_empty():
                self._empty = False
                self._boiled = False

    def drain(self) -> None:
        with self._lock:
            if not self.is_empty() and self.is_boiled():
                self._empty = True

    def boil(self) -> None:
        with self._lock:
            if not self.is_empty() and not self.is_boiled():
                self._boiled = True

    def is_empty(self) -> bool:
        with self._lock:
            return self._empty

    def is_boiled(self) -> bool:
        with self._lock:
            return self._boiled
