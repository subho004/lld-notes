"""ImageProxy: Virtual Proxy for ImageIcon. Defers the expensive creation of
the real icon until it is first painted, showing a placeholder meanwhile.
"""
from __future__ import annotations

from typing import Optional

from swing_sim import Component, Graphics, Icon, ImageIcon, SimulatedThread


class ImageProxy(Icon):
    """Virtual Proxy: implements Icon and lazily creates the real ImageIcon."""
    def __init__(self, url: str) -> None:
        self.image_icon: Optional[ImageIcon] = None
        self.image_url = url
        self.retrieval_thread: Optional[SimulatedThread] = None
        self.retrieving = False

    def get_icon_width(self) -> int:
        if self.image_icon is not None:
            return self.image_icon.get_icon_width()
        # Placeholder size (the window size) until the real icon exists.
        return 800

    def get_icon_height(self) -> int:
        if self.image_icon is not None:
            return self.image_icon.get_icon_height()
        return 600

    def set_image_icon(self, image_icon: ImageIcon) -> None:
        self.image_icon = image_icon

    def paint_icon(self, c: Component, g: Graphics, x: int, y: int) -> None:
        if self.image_icon is not None:
            self.image_icon.paint_icon(c, g, x, y)
        else:
            g.draw_string("Loading album cover, please wait...", x + 300, y + 190)
            # Start at most one background load; the flag guards repeated repaints.
            if not self.retrieving:
                self.retrieving = True

                # Closure captures c so the finished load can request a repaint (Java: Thread).
                def run() -> None:
                    self.set_image_icon(ImageIcon(self.image_url, "Album Cover"))
                    c.repaint()

                self.retrieval_thread = SimulatedThread(run)
                self.retrieval_thread.start()
