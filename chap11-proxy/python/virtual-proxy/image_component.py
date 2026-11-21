"""ImageComponent: the virtual proxy's client. It paints any Icon and does
not know whether it holds an ImageProxy or a real ImageIcon.
"""
from swing_sim import Component, Graphics, Icon


class ImageComponent(Component):
    """Client of the Icon interface; set_icon() swaps in a new proxy per album."""
    def __init__(self, icon: Icon) -> None:
        super().__init__()
        self.icon = icon

    def set_icon(self, icon: Icon) -> None:
        self.icon = icon

    def repaint(self) -> None:
        super().repaint()
        self.paint_component(Graphics())  # the toolkit would paint asynchronously

    def paint_component(self, g: Graphics) -> None:
        w = self.icon.get_icon_width()
        h = self.icon.get_icon_height()
        x = (800 - w) // 2
        y = (600 - h) // 2
        self.icon.paint_icon(self, g, x, y)
