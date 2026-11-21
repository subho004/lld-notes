"""Concrete Subject: HeartModel, the model that HeartAdapter adapts for the view."""

from __future__ import annotations

from heart_model_interface import HeartModelInterface
from observers import BeatObserver, BPMObserver


class _Random:
    """Small deterministic LCG (same constants in the C++ port) replacing
    java.util.Random(System.currentTimeMillis())."""

    def __init__(self, seed: int) -> None:
        self.state = seed & 0x7FFFFFFF

    def next_int(self, bound: int) -> int:
        self.state = (self.state * 1103515245 + 12345) & 0x7FFFFFFF
        return (self.state >> 16) % bound


class HeartModel(HeartModelInterface):
    """Simulated heart with a fixed-seed generator, so output is reproducible
    (Java seeds from the clock and varies per run)."""

    def __init__(self, seed: int = 42) -> None:
        self.beat_observers: list[BeatObserver] = []
        self.bpm_observers: list[BPMObserver] = []
        self.time = 1000
        self.bpm = 90
        self.random = _Random(seed)
        self.lastrate = -1
        self.now = 0
        self.next_iteration_at = 0

    def advance(self, ms: int) -> None:
        """Runs the body of Java's `while (true)` loop for every iteration that
        falls before now+ms; Thread.sleep(time) becomes next_iteration_at."""
        target = self.now + ms
        while self.next_iteration_at < target:
            self.now = self.next_iteration_at
            self.run_once()
            self.next_iteration_at = self.now + self.time
        self.now = target

    def run_once(self) -> None:
        change = self.random.next_int(10)
        if self.random.next_int(2) == 0:
            change = 0 - change
        rate = 60000 // (self.time + change)
        # Accept the change only when the new rate stays in a plausible range.
        if rate < 120 and rate > 50:
            self.time += change
            self.notify_beat_observers()
            if rate != self.lastrate:  # BPM observers hear only about real changes
                self.lastrate = rate
                self.notify_bpm_observers()

    def get_heart_rate(self) -> int:
        return 60000 // self.time

    def register_beat_observer(self, o: BeatObserver) -> None:
        self.beat_observers.append(o)

    def remove_beat_observer(self, o: BeatObserver) -> None:
        if o in self.beat_observers:
            self.beat_observers.remove(o)

    def notify_beat_observers(self) -> None:
        for observer in list(self.beat_observers):
            observer.update_beat()

    def register_bpm_observer(self, o: BPMObserver) -> None:
        self.bpm_observers.append(o)

    def remove_bpm_observer(self, o: BPMObserver) -> None:
        if o in self.bpm_observers:
            self.bpm_observers.remove(o)

    def notify_bpm_observers(self) -> None:
        for observer in list(self.bpm_observers):
            observer.update_bpm()
