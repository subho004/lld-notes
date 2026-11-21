"""Console stand-ins for the Swing/AWT bits used by the virtual proxy demo.

* Graphics.draw_string / ImageIcon.paint_icon just print what would be drawn.
* Thread is replaced by SimulatedThread + a Scheduler whose clock advances
  one tick per Scheduler.tick() call, so "loading" is deterministic.
"""
from __future__ import annotations

from abc import ABC, abstractmethod
from typing import Callable, List


class Graphics:
    """Console stand-in for java.awt.Graphics."""

    def draw_string(self, text: str, x: int, y: int) -> None:
        print(f"  [draw] string '{text}' at ({x},{y})")


class Component:
    """Console stand-in for a Swing component; counts and logs repaint requests."""

    def __init__(self) -> None:
        self.paint_requests = 0

    def repaint(self) -> None:
        self.paint_requests += 1
        print("  [repaint requested]")


class Icon(ABC):
    """Subject interface (javax.swing.Icon) shared by ImageIcon and ImageProxy."""

    @abstractmethod
    def get_icon_width(self) -> int: ...

    @abstractmethod
    def get_icon_height(self) -> int: ...

    @abstractmethod
    def paint_icon(self, c: Component, g: Graphics, x: int, y: int) -> None: ...


class ImageIcon(Icon):
    """Fake ImageIcon: constructing it is the 'slow download'. Size is fixed."""

    def __init__(self, url: str, description: str) -> None:
        self.url = url
        self.description = description

    def get_icon_width(self) -> int:
        return 300

    def get_icon_height(self) -> int:
        return 300

    def paint_icon(self, c: Component, g: Graphics, x: int, y: int) -> None:
        print(f"  [draw] image '{self.description}' ({self.url}) at ({x},{y})")


class Scheduler:
    """Runs queued 'threads' once their delay (in ticks) has elapsed."""

    def __init__(self) -> None:
        self._pending: List["SimulatedThread"] = []

    def add(self, t: "SimulatedThread") -> None:
        self._pending.append(t)

    def tick(self) -> None:
        for t in list(self._pending):
            t.remaining -= 1
            if t.remaining <= 0:
                self._pending.remove(t)
                t.target()


# Single shared clock; test drives advance it with scheduler.tick().
scheduler = Scheduler()


class SimulatedThread:
    """Deterministic replacement for java.lang.Thread; runs after delay_ticks ticks."""

    def __init__(self, target: Callable[[], None], delay_ticks: int = 2) -> None:
        self.target = target
        self.remaining = delay_ticks

    def start(self) -> None:
        scheduler.add(self)
