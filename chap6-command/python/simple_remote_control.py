"""Simplest Invoker: holds one Command and triggers it on button press."""
from typing import Optional

from command import Command


class SimpleRemoteControl:
    """Invoker with a single slot."""

    def __init__(self) -> None:
        self.slot: Optional[Command] = None

    def set_command(self, command: Command) -> None:
        self.slot = command

    def button_was_pressed(self) -> None:
        assert self.slot is not None
        self.slot.execute()

    def undo_button_was_pressed(self) -> None:
        assert self.slot is not None
        self.slot.undo()
