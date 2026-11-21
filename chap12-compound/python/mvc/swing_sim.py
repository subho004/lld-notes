"""Tiny headless stand-ins for the Swing widgets used by DJView.

Nothing is drawn.  Buttons and menu items keep an enabled flag and a list of
listeners, and ``click()`` plays the role of the user pressing them, so main()
can drive the "GUI" deterministically.
"""
from __future__ import annotations

from typing import Callable


class ActionEvent:
    """Simulated java.awt.event.ActionEvent: carries the widget that was clicked."""

    def __init__(self, source: object) -> None:
        self.source = source

    def get_source(self) -> object:
        return self.source


ActionListener = Callable[[ActionEvent], None]


class Label:
    """Simulated JLabel: just holds text."""

    def __init__(self, text: str = "") -> None:
        self.text = text

    def set_text(self, text: str) -> None:
        self.text = text

    def get_text(self) -> str:
        return self.text


class TextField(Label):
    """Simulated JTextField: same behavior as Label is enough here."""

    pass


class Button:
    """Simulated JButton: enabled flag plus listeners, driven by click()."""

    def __init__(self, text: str) -> None:
        self.text = text
        self.enabled = True
        self.listeners: list[ActionListener] = []

    def add_action_listener(self, listener: ActionListener) -> None:
        self.listeners.append(listener)

    def set_enabled(self, enabled: bool) -> None:
        self.enabled = enabled

    def is_enabled(self) -> bool:
        return self.enabled

    def click(self) -> None:
        if not self.enabled:
            print(f"[GUI] '{self.text}' is disabled, click ignored")
            return
        print(f"[GUI] click '{self.text}'")
        for listener in self.listeners:
            listener(ActionEvent(self))


class MenuItem(Button):
    """Simulated JMenuItem: behaves exactly like a Button."""

    pass
