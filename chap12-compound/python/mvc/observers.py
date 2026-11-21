"""Observer interfaces for the model, plus callable-based wrappers."""

from __future__ import annotations

from abc import ABC, abstractmethod
from typing import Callable


class BeatObserver(ABC):
    """Observer interface: notified on every beat."""

    @abstractmethod
    def update_beat(self) -> None: ...


class BPMObserver(ABC):
    """Observer interface: notified when the BPM changes."""

    @abstractmethod
    def update_bpm(self) -> None: ...


class FunctionBeatObserver(BeatObserver):
    """Stands in for Java's lambda-as-BeatObserver."""

    def __init__(self, fn: Callable[[], None]) -> None:
        self.fn = fn

    def update_beat(self) -> None:
        self.fn()


class FunctionBPMObserver(BPMObserver):
    """Stands in for Java's lambda-as-BPMObserver."""

    def __init__(self, fn: Callable[[], None]) -> None:
        self.fn = fn

    def update_bpm(self) -> None:
        self.fn()
