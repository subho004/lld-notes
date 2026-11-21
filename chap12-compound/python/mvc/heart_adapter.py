"""Adapter: HeartAdapter makes a HeartModel look like a BeatModelInterface."""

from __future__ import annotations

from beat_model_interface import BeatModelInterface
from heart_model_interface import HeartModelInterface
from observers import BeatObserver, BPMObserver


class HeartAdapter(BeatModelInterface):
    """Adapter: lets a HeartModel be used where a BeatModel is expected."""

    def __init__(self, heart: HeartModelInterface) -> None:
        self.heart = heart

    # Controls that make no sense for a heart are deliberately no-ops.
    def initialize(self) -> None:
        pass

    def on(self) -> None:
        pass

    def off(self) -> None:
        pass

    def get_bpm(self) -> int:
        # Translate: a heart rate is the BPM.
        return self.heart.get_heart_rate()

    def set_bpm(self, bpm: int) -> None:
        pass

    def register_beat_observer(self, o: BeatObserver) -> None:
        # Observer calls are forwarded to the adaptee.
        self.heart.register_beat_observer(o)

    def remove_beat_observer(self, o: BeatObserver) -> None:
        self.heart.remove_beat_observer(o)

    def register_bpm_observer(self, o: BPMObserver) -> None:
        self.heart.register_bpm_observer(o)

    def remove_bpm_observer(self, o: BPMObserver) -> None:
        self.heart.remove_bpm_observer(o)

    def advance(self, ms: int) -> None:
        self.heart.advance(ms)
