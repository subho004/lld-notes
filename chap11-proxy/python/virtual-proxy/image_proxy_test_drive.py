"""Virtual-proxy demo. Replaces the Swing menu with explicit menu_item_clicked()
calls and drives the fake clock with scheduler.tick().
"""
from __future__ import annotations

from typing import Dict

from image_component import ImageComponent
from image_proxy import ImageProxy
from swing_sim import Graphics, scheduler


class Frame:
    """Minimal JFrame: repaint() paints its single component to the console."""

    def __init__(self, title: str) -> None:
        self.title = title
        self.component: ImageComponent | None = None

    def repaint(self) -> None:
        assert self.component is not None
        self.component.paint_component(Graphics())


class ImageProxyTestDrive:
    """Client wiring: ImageComponent shows an ImageProxy for the chosen album."""

    def __init__(self) -> None:
        # Insertion order instead of Java's Hashtable order.
        self.albums: Dict[str, str] = {
            "Buddha Bar": "http://images.amazon.com/images/P/B00009XBYK.01.LZZZZZZZ.jpg",
            "Ima": "http://images.amazon.com/images/P/B000005IRM.01.LZZZZZZZ.jpg",
            "Karma": "http://images.amazon.com/images/P/B000005DCB.01.LZZZZZZZ.gif",
            "MCMXC a.D.": "http://images.amazon.com/images/P/B000002URV.01.LZZZZZZZ.jpg",
            "Northern Exposure": "http://images.amazon.com/images/P/B000003SFN.01.LZZZZZZZ.jpg",
            "Selected Ambient Works, Vol. 2":
                "http://images.amazon.com/images/P/B000002MNZ.01.LZZZZZZZ.jpg",
        }
        self.frame = Frame("Album Cover Viewer")
        initial_url = self.albums["Selected Ambient Works, Vol. 2"]
        self.image_component = ImageComponent(ImageProxy(initial_url))
        self.frame.component = self.image_component
        print(f"Frame '{self.frame.title}' visible, menu: Favorite Albums {list(self.albums)}")

    def menu_item_clicked(self, name: str) -> None:
        """What each JMenuItem's ActionListener does."""
        print(f"Menu item '{name}' clicked")
        self.image_component.set_icon(ImageProxy(self.get_album_url(name)))
        self.frame.repaint()

    def get_album_url(self, name: str) -> str:
        return self.albums[name]


def main() -> None:
    drive = ImageProxyTestDrive()
    print("Initial paint:")
    drive.frame.repaint()
    for tick in (1, 2):
        print(f"Tick {tick}: background loading advances")
        scheduler.tick()

    drive.menu_item_clicked("Karma")
    print("Window repaints while still loading:")
    drive.frame.repaint()
    for tick in (1, 2):
        print(f"Tick {tick}: background loading advances")
        scheduler.tick()
    drive.menu_item_clicked("Ima")
    scheduler.tick()
    scheduler.tick()
    print("Done")


if __name__ == "__main__":
    main()
