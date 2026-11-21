"""Headless stand-in for the Swing MyFrame (no tkinter / display needed).

Frame plays JFrame; Graphics plays java.awt.Graphics by printing draw calls.
paint() is the template-method hook that the 'toolkit' calls; here main()
plays the toolkit and calls it when the frame becomes visible.
"""


class Graphics:
    """Simulated java.awt.Graphics: prints each draw call instead of drawing."""

    def draw_string(self, text: str, x: int, y: int) -> None:
        print(f"  drawString({text!r}, {x}, {y})")


class Frame:
    """Simulated JFrame: owns the framework side, i.e. calls the paint() hook itself."""

    def __init__(self, title: str) -> None:
        self.title = title
        self.width = 0
        self.height = 0
        self.visible = False

    def set_size(self, width: int, height: int) -> None:
        self.width, self.height = width, height

    def set_visible(self, visible: bool) -> None:
        self.visible = visible
        if visible:
            print(f"Frame '{self.title}' shown ({self.width}x{self.height})")
            self.paint(Graphics())  # the toolkit calls the paint hook

    # Default hook behaviour (JFrame's background painting).
    def paint(self, g: Graphics) -> None:
        print("  super.paint: background cleared")


class MyFrame(Frame):
    """Concrete subclass: overrides the paint() hook, as Swing code would."""

    def __init__(self, title: str) -> None:
        super().__init__(title)
        self.set_size(300, 300)

    def paint(self, g: Graphics) -> None:
        super().paint(g)
        g.draw_string("Hello, World!", 100, 100)


def main() -> None:
    frame = MyFrame("Hello, World!")
    frame.set_visible(True)


if __name__ == "__main__":
    main()
