"""Concrete Subject (Model): BeatModel, which notifies beat and BPM observers."""

from __future__ import annotations

from beat_model_interface import BeatModelInterface
from observers import BeatObserver, BPMObserver


class BeatModel(BeatModelInterface):
    """Simulated beat clock: no thread, no sleep, no audio.

    The Java thread loop ``playBeat(); notifyBeatObservers(); sleep(60000/bpm)``
    becomes advance(ms), which moves a virtual clock forward and fires every
    beat that is due strictly before the new time.
    """

    def __init__(self) -> None:
        self.beat_observers: list[BeatObserver] = []
        self.bpm_observers: list[BPMObserver] = []
        self.bpm = 90
        self.stop = False
        self.running = False
        self.now = 0
        self.next_beat_at = 0

    def initialize(self) -> None:
        print("clap.wav not found; running without audio")

    def on(self) -> None:
        self.bpm = 90
        self.notify_bpm_observers()
        self.stop = False
        self.running = True
        self.next_beat_at = self.now  # the Java thread beats immediately

    def off(self) -> None:
        self.stop_beat()
        self.stop = True
        self.running = False

    def advance(self, ms: int) -> None:
        target = self.now + ms
        while self.running and not self.stop and self.next_beat_at < target:
            self.now = self.next_beat_at
            self.play_beat()
            self.notify_beat_observers()  # Observer: push each beat to the views
            self.next_beat_at = self.now + self.sleep_ms()
        self.now = target

    def sleep_ms(self) -> int:
        # 60000 / bpm plus 1 ms of simulated scheduling overhead, so a beat
        # that would land exactly on a boundary behaves like the real thread.
        return 60000 // self.get_bpm() + 1

    def set_bpm(self, bpm: int) -> None:
        self.bpm = bpm
        self.notify_bpm_observers()

    def get_bpm(self) -> int:
        return self.bpm

    def register_beat_observer(self, o: BeatObserver) -> None:
        self.beat_observers.append(o)

    def remove_beat_observer(self, o: BeatObserver) -> None:
        if o in self.beat_observers:
            self.beat_observers.remove(o)

    def notify_beat_observers(self) -> None:
        # Iterate over a copy so observers may unregister during the callback.
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

    def play_beat(self) -> None:
        pass  # no audio in the console port

    def stop_beat(self) -> None:
        pass
