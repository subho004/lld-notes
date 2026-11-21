"""Strategy interface: what the view may ask a controller to do."""

from __future__ import annotations

from abc import ABC, abstractmethod


class ControllerInterface(ABC):
    """Strategy interface; the view only knows this, never a concrete controller."""

    @abstractmethod
    def start(self) -> None: ...

    @abstractmethod
    def stop(self) -> None: ...

    @abstractmethod
    def increase_bpm(self) -> None: ...

    @abstractmethod
    def decrease_bpm(self) -> None: ...

    @abstractmethod
    def set_bpm(self, bpm: int) -> None: ...
