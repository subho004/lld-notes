"""BeatBar: part of the View (replaces the Swing JProgressBar and its animation thread)."""

from __future__ import annotations


class BeatBar:
    """JProgressBar + Thread in Java; here step() is one 50 ms tick of the
    decay loop (value = int(value * .75)), called by DJView.tick()."""

    def __init__(self) -> None:
        self.maximum = 100
        self.value = 0

    def set_value(self, value: int) -> None:
        self.value = value

    def get_value(self) -> int:
        return self.value

    def step(self) -> None:
        # Matches the Java decay loop: drop to 75% each frame, truncating.
        self.value = int(self.value * 0.75)

    def render(self) -> str:
        # Text rendering stands in for painting: 10 cells, one per 10 points.
        filled = self.value // 10
        return "|" + "#" * filled + "." * (10 - filled) + "|"
