"""Console simulation of the Swing observer example (no GUI / tkinter).

FakeButton plays the role of JButton (the subject): listeners register with
add_action_listener and are called when click() is invoked (here from main,
standing in for the user pressing the button).
Deviation from Java: the frame/button are console fakes because Swing needs a display.
"""
import sys
from abc import ABC, abstractmethod
from typing import Callable, List, Optional


class ActionEvent:
    # Event object passed to every listener (empty, as nothing is read from it).
    pass


class ActionListener(ABC):
    # Observer interface (Swing's ActionListener).
    @abstractmethod
    def action_performed(self, event: ActionEvent) -> None:
        ...


class FakeButton:
    # Stand-in for JButton: the Subject that notifies its listeners on click.
    def __init__(self, text: str) -> None:
        self.text = text
        self._listeners: List[Callable[[ActionEvent], None]] = []

    def add_action_listener(self, listener) -> None:
        # Accept either an ActionListener object or a plain callable (lambda).
        if isinstance(listener, ActionListener):
            self._listeners.append(listener.action_performed)
        else:
            self._listeners.append(listener)

    def click(self) -> None:
        # Notify all listeners in registration order.
        event = ActionEvent()
        for listener in self._listeners:
            listener(event)


class FakeFrame:
    # Stand-in for JFrame; "showing" it just prints one line.
    def __init__(self, title: str) -> None:
        self.title = title
        self.size = (0, 0)
        self.visible = False
        self._content: Optional[FakeButton] = None

    def add(self, button: FakeButton) -> None:
        self._content = button

    def set_size(self, w: int, h: int) -> None:
        self.size = (w, h)

    def set_visible(self, visible: bool) -> None:
        self.visible = visible
        if visible:
            print(f"[frame '{self.title}' {self.size[0]}x{self.size[1]} shown with "
                  f"button '{self._content.text}']")


class AngelListener(ActionListener):
    # Concrete Observer.
    def action_performed(self, event: ActionEvent) -> None:
        print("Don't do it, you might regret it!")


class DevilListener(ActionListener):
    # Concrete Observer.
    def action_performed(self, event: ActionEvent) -> None:
        print("Come on, do it!")


class SwingObserverExample:
    def __init__(self) -> None:
        self.frame: Optional[FakeFrame] = None

    def go_normal(self) -> None:
        self.frame = FakeFrame("Swing Observer - Normal")
        button = FakeButton("Should I do it?")
        button.add_action_listener(AngelListener())
        button.add_action_listener(DevilListener())
        self._show_frame(button)

    def go_lambda(self) -> None:
        # Same observers as go_normal, but as lambdas instead of listener classes.
        self.frame = FakeFrame("Swing Observer - Lambda")
        button = FakeButton("Should I do it?")
        button.add_action_listener(lambda event: print("Don't do it, you might regret it!"))
        button.add_action_listener(lambda event: print("Come on, do it!"))
        self._show_frame(button)

    def _show_frame(self, button: FakeButton) -> None:
        assert self.frame is not None
        self.frame.add(button)
        self.frame.set_size(300, 300)
        self.frame.set_visible(True)
        # Simulation only: stands in for a real user click.
        print("[user clicks the button]")
        button.click()


def main() -> None:
    mode = sys.argv[1] if len(sys.argv) > 1 else "normal"
    example = SwingObserverExample()
    if mode.lower() == "lambda":
        example.go_lambda()
    else:
        example.go_normal()


if __name__ == "__main__":
    main()
