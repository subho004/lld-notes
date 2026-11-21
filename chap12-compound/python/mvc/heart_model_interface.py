"""Subject interface for HeartModel, the "incompatible" model the adapter wraps."""

from __future__ import annotations

from abc import ABC, abstractmethod

from observers import BeatObserver, BPMObserver


class HeartModelInterface(ABC):
    @abstractmethod
    def get_heart_rate(self) -> int: ...

    @abstractmethod
    def register_beat_observer(self, o: BeatObserver) -> None: ...

    @abstractmethod
    def remove_beat_observer(self, o: BeatObserver) -> None: ...

    @abstractmethod
    def register_bpm_observer(self, o: BPMObserver) -> None: ...

    @abstractmethod
    def remove_bpm_observer(self, o: BPMObserver) -> None: ...

    # Simulation hook replacing the Java model's own thread.
    def advance(self, ms: int) -> None:
        pass
