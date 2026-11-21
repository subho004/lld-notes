"""Model interface (Subject side of Observer) that views and controllers depend on."""

from __future__ import annotations

from abc import ABC, abstractmethod

from observers import BeatObserver, BPMObserver


class BeatModelInterface(ABC):
    """Java overloads registerObserver/removeObserver on the observer type;
    Python cannot, so the two flavours get distinct names."""

    @abstractmethod
    def initialize(self) -> None: ...

    @abstractmethod
    def on(self) -> None: ...

    @abstractmethod
    def off(self) -> None: ...

    @abstractmethod
    def set_bpm(self, bpm: int) -> None: ...

    @abstractmethod
    def get_bpm(self) -> int: ...

    @abstractmethod
    def register_beat_observer(self, o: BeatObserver) -> None: ...

    @abstractmethod
    def remove_beat_observer(self, o: BeatObserver) -> None: ...

    @abstractmethod
    def register_bpm_observer(self, o: BPMObserver) -> None: ...

    @abstractmethod
    def remove_bpm_observer(self, o: BPMObserver) -> None: ...

    # Simulation hook (replaces the Java model's own thread + Thread.sleep).
    def advance(self, ms: int) -> None:
        # Default no-op so models without a clock (e.g. adapters) need not override.
        pass
